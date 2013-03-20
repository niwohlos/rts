#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "camera.hpp"
#include "shader.hpp"


class terrain
{
    public:
        terrain(const char *normal_height, const char *texture);
        ~terrain(void);

        void draw(void);
        void update_camera(camera *cam);


    private:
        unsigned normal_height_gl_id, texture_gl_id;

        program *display_program;
        int display_program_mvp_loc, display_program_nrm_loc, display_program_inc_loc;

        unsigned vertex_buffer;
        int vertex_buffer_vertices;
};

#endif
