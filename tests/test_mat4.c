#include <assert.h>
#include <math.h>
#include <toolcl/mat4.h>
#include <toolcl/math.h>
#include <toolcl/vec3.h>

static int near(float a, float b)
{
    return fabsf(a - b) < 0.0001f;
}

int main(void)
{
    ToolCL_Mat4 identity = toolcl_mat4_identity();
    ToolCL_Mat4 translation;
    ToolCL_Mat4 scale;
    ToolCL_Mat4 rotation;
    ToolCL_Mat4 result;
    ToolCL_Vec3 vector;
    ToolCL_Vec3 transformed;

    assert(near(identity.data[0], 1.0f));
    assert(near(identity.data[5], 1.0f));
    assert(near(identity.data[10], 1.0f));
    assert(near(identity.data[15], 1.0f));

    translation = toolcl_mat4_translate(toolcl_vec3(2.0f, 3.0f, 4.0f));
    vector = toolcl_vec3(1.0f, 1.0f, 1.0f);
    transformed = toolcl_mat4_transform_vec3(translation, vector);

    assert(near(transformed.x, 3.0f));
    assert(near(transformed.y, 4.0f));
    assert(near(transformed.z, 5.0f));

    scale = toolcl_mat4_scale(toolcl_vec3(2.0f, 3.0f, 4.0f));
    transformed = toolcl_mat4_transform_vec3(scale, vector);

    assert(near(transformed.x, 2.0f));
    assert(near(transformed.y, 3.0f));
    assert(near(transformed.z, 4.0f));

    rotation = toolcl_mat4_rotate_z(toolcl_radians(90.0f));
    transformed = toolcl_mat4_transform_vec3(
        rotation,
        toolcl_vec3(1.0f, 0.0f, 0.0f)
    );

    assert(near(transformed.x, 0.0f));
    assert(near(transformed.y, 1.0f));

    result = toolcl_mat4_mul(identity, translation);

    assert(near(result.data[12], 2.0f));
    assert(near(result.data[13], 3.0f));
    assert(near(result.data[14], 4.0f));

    return 0;
}
