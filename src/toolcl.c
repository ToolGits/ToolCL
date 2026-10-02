/* ToolCL website backend: Kore + SQLite. Serves the wall and a tiny JSON API. */
#include <kore/kore.h>
#include <kore/http.h>
#include <sqlite3.h>
#include <stdlib.h>

#include "assets.h"

int	page(struct http_request *);
int	api_version(struct http_request *);
int	api_releases(struct http_request *);

static sqlite3	*db;

#define COLS	"version,codename,channel,released,notes"

/* Runs once in every worker process. */
void
kore_worker_configure(void)
{
	const char *path = getenv("TOOLCL_DB");

	if (sqlite3_open_v2(path ? path : "toolcl.db", &db,
	    SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK)
		fatal("toolcl: cannot open database");
	sqlite3_busy_timeout(db, 2000);
}

static void
jstr(struct kore_buf *b, const unsigned char *s)
{
	kore_buf_append(b, "\"", 1);
	for (; s != NULL && *s != '\0'; s++) {
		if (*s == '"' || *s == '\\') {
			kore_buf_append(b, "\\", 1);
			kore_buf_append(b, s, 1);
		} else if (*s < 0x20) {
			kore_buf_appendf(b, "\\u%04x", *s);
		} else {
			kore_buf_append(b, s, 1);
		}
	}
	kore_buf_append(b, "\"", 1);
}

static void
jrow(struct kore_buf *b, sqlite3_stmt *st)
{
	static const char *key[] = { "version", "codename", "channel",
	    "released", "notes" };
	int i;

	kore_buf_append(b, "{", 1);
	for (i = 0; i < 5; i++) {
		if (i > 0)
			kore_buf_append(b, ",", 1);
		kore_buf_appendf(b, "\"%s\":", key[i]);
		jstr(b, sqlite3_column_text(st, i));
	}
	kore_buf_append(b, "}", 1);
}

static int
reply(struct http_request *req, const char *sql, int many)
{
	sqlite3_stmt	*st;
	struct kore_buf	*b;
	u_int8_t	*out;
	size_t		len;
	int		n = 0;

	if (req->method != HTTP_METHOD_GET) {
		http_response(req, 405, NULL, 0);
		return (KORE_RESULT_OK);
	}
	if (sqlite3_prepare_v2(db, sql, -1, &st, NULL) != SQLITE_OK) {
		http_response(req, 500, NULL, 0);
		return (KORE_RESULT_OK);
	}

	b = kore_buf_alloc(256);
	if (many)
		kore_buf_append(b, "[", 1);
	while (sqlite3_step(st) == SQLITE_ROW) {
		if (many && n > 0)
			kore_buf_append(b, ",", 1);
		jrow(b, st);
		n++;
	}
	if (many)
		kore_buf_append(b, "]", 1);
	sqlite3_finalize(st);

	out = kore_buf_release(b, &len);
	if (n == 0 && !many) {
		http_response(req, 404, NULL, 0);
	} else {
		http_response_header(req, "content-type", "application/json");
		http_response_header(req, "cache-control", "no-store");
		http_response(req, 200, out, len);
	}
	kore_free(out);
	return (KORE_RESULT_OK);
}

int
api_version(struct http_request *req)
{
	return (reply(req, "SELECT " COLS " FROM releases "
	    "WHERE channel='stable' ORDER BY released DESC, id DESC LIMIT 1", 0));
}

int
api_releases(struct http_request *req)
{
	return (reply(req, "SELECT " COLS " FROM releases "
	    "ORDER BY released DESC, id DESC LIMIT 50", 1));
}

int
page(struct http_request *req)
{
	if (req->method != HTTP_METHOD_GET) {
		http_response(req, 405, NULL, 0);
		return (KORE_RESULT_OK);
	}
	http_response_header(req, "content-type", "text/html; charset=utf-8");
	http_response(req, 200, asset_index_html, asset_len_index_html);
	return (KORE_RESULT_OK);
}
