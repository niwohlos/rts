#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "camera.hpp"
#include "shader.hpp"


class terrain
{
    public:
        terrain(const char *height_map);
        ~terrain(void);

        void draw(void);
        void update_camera(camera *cam);


    private:
        unsigned height_map_gl_id;

        program *display_program;
        int display_program_mvp_loc;
};

#endif
