#include "opengl.hpp"


int ogl_major, ogl_minor;


void init_opengl(void)
{
    glGetIntegerv(GL_MAJOR_VERSION, &ogl_major);
    glGetIntegerv(GL_MINOR_VERSION, &ogl_minor);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
}
