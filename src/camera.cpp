#include <cmath>

#include "camera.hpp"
#include "types.hpp"


camera::camera(float fov, float aspect):
    projection(mat4::projection(fov, aspect, .1f, 1000.f)),
    modelview(mat4::identity().translated(vec3(0.f, 5.f, 0.f)).rotated(M_PI_2, vec3(1.f, 0.f, 0.f)))
{
}
