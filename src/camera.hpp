#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "types.hpp"


class camera
{
    public:
        camera(float fov, float aspect);
        ~camera(void);


        mat4 projection, modelview;
};

#endif
