#include "opengl.hpp"

extern "C"
{
#include <sys/time.h>
}


int ogl_major, ogl_minor;


void init_opengl(void)
{
    glGetIntegerv(GL_MAJOR_VERSION, &ogl_major);
    glGetIntegerv(GL_MINOR_VERSION, &ogl_minor);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
}


float get_fps(void)
{
    static struct timeval tv;
    static bool valid = false;

    int usec = tv.tv_usec, sec = tv.tv_sec;

    gettimeofday(&tv, NULL);

    if (!valid)
    {
        valid = true;
        return 0.f;
    }


    return 1000000.f / ((tv.tv_sec - sec) * 1000000 + tv.tv_usec - usec);
}
