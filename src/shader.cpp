#include <cstdio>
#include <initializer_list>

extern "C"
{
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>
}

#include "shader.hpp"
#include "types.hpp"


shader::shader(const char *file)
{
    int len = strlen(file);

    if (len < 9)
    {
        throw 0; // TODO
    }


    int type;

    if (!strcmp(&file[len - 9], "vert.glsl"))
    {
        type = GL_VERTEX_SHADER;
    }
    else if (!strcmp(&file[len - 9], "geom.glsl"))
    {
        type = GL_GEOMETRY_SHADER;
    }
    else if (!strcmp(&file[len - 9], "frag.glsl"))
    {
        type = GL_FRAGMENT_SHADER;
    }
    else
    {
        throw 0; // TODO
    }


    FILE *fp = fopen(file, "r");

    if (fp == NULL)
    {
        throw 1; // TODO
    }


    fseek(fp, 0, SEEK_END);
    int sz = ftell(fp);
    rewind(fp);

    char *content = new char[sz];

    fread(content, 1, sz, fp);

    fclose(fp);


    id = glCreateShader(type);

    glShaderSource(id, 1, &content, &sz);
    delete content;


    glCompileShader(id);

    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glDeleteShader(id);
        throw 2; // TODO (besides exception: emit error message)
    }
}


shader::~shader(void)
{
    glDeleteShader(id);
}


program::program(std::initializer_list<const shader *> shaders)
{
    id = glCreateProgram();

    for (const shader *sh: shaders)
    {
         glAttachShader(id, sh->id);
    }

    glLinkProgram(id);

    int status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (!status)
    {
        glDeleteProgram(id);
        throw 2; // TODO (besides exception: emit error message)
    }
}


program::~program(void)
{
    glDeleteProgram(id);
}


void program::use(void)
{
    glUseProgram(id);
}


int program::get_uniform_location(const char *name)
{
    return glGetUniformLocation(id, name);
}


void program::set_uniform(int location, const mat4 &m)
{
    use();

    glUniformMatrix4fv(location, 1, false, m.d);
}
