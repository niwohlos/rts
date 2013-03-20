#include <cmath>

#include "camera.hpp"
#include "types.hpp"


camera::camera(float fov, float aspect):
    projection(mat4::projection(fov, aspect, .1f, 1000.f)),
    modelview(mat4::identity().rotated(-M_PI_4, vec3(1.f, 0.f, 0.f)).rotated(M_PI_4, vec3(0.f, 1.f, 0.f)).translated(vec3(-.8f, -.5f, -.2f)))
{
}
