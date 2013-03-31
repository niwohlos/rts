#include <cmath>

#include "camera.hpp"
#include "types.hpp"


camera::camera(float fov, float aspect):
    projection(mat4::projection(fov, aspect, .1f, 1000.f)),
    modelview(mat4::identity().rotated(-M_PI_4, vec3(1.f, 0.f, 0.f)).rotated(M_PI_4, vec3(0.f, 1.f, 0.f)).translated(vec3(-.8f, -.5f, -.2f)))
{
}

void camera::move(float d, const vec3 &v)
{
    modelview.d[12] += v.x * d;
    modelview.d[13] += v.y * d;
    modelview.d[14] += v.z * d;
}

void camera::move_global(float d, const vec3 &v)
{
    modelview.translate(v * d);
}
