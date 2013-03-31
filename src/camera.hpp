#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "types.hpp"


class camera
{
    public:
        camera(float fov, float aspect);
        ~camera(void);

        void move(float t, const vec3 &v);
        void move_global(float t, const vec3 &v);

        mat4 projection, modelview;
};

#endif
