#ifndef OPENGL_HPP
#define OPENGL_HPP

#define GL_GLEXT_PROTOTYPES

extern "C"
{
#include <GL/gl.h>
#include <GL/glext.h>
}


void init_opengl(void);


extern int ogl_major, ogl_minor;

#endif
