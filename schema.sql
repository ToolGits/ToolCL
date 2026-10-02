PRAGMA journal_mode = WAL;

CREATE TABLE IF NOT EXISTS releases (
	id       INTEGER PRIMARY KEY,
	version  TEXT NOT NULL,
	codename TEXT NOT NULL DEFAULT '',
	channel  TEXT NOT NULL DEFAULT 'stable' CHECK (channel IN ('stable','nightly')),
	released TEXT NOT NULL,
	notes    TEXT NOT NULL DEFAULT ''
);

-- Placeholder seed: replace with real ToolCL releases.
INSERT INTO releases (version, codename, channel, released, notes)
VALUES ('0.1.0', 'Workbench', 'stable', '2026-10-02', 'Placeholder release.');
