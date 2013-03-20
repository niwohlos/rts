#include "opengl.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>

extern "C"
{
#include <dirent.h>
#include <libgen.h>
}

#include "shader.hpp"
#include "types.hpp"


shader::shader(const char *file)
{
    printf("Loading shader %s...\n", file);


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


program::program(const char *base)
{
    size_t len = strlen(base) + 1;

    char d1[len], d2[len];
    memcpy(d1, base, len);
    memcpy(d2, base, len);

    const char *dir  = dirname(d1);
    const char *file = basename(d2);

    size_t flen = strlen(file);


    int this_ver = ogl_major * 10 + ogl_minor;

    int vert_max_ver = 0, geom_max_ver = 0, frag_max_ver = 0;


    DIR *dp = opendir(dir);

    if (dp == NULL)
    {
        throw 0; // TODO
    }

    struct dirent *ent;
    while ((ent = readdir(dp)) != NULL)
    {
        if (!strncmp(ent->d_name, file, flen) && (ent->d_name[flen] == '.'))
        {
            int file_ver = atoi(&ent->d_name[flen + 1]);

            int *appr_ver = NULL;
            if (!strcmp(&ent->d_name[flen + 3], ".vert.glsl"))
            {
                appr_ver = &vert_max_ver;
            }
            else if (!strcmp(&ent->d_name[flen + 3], ".geom.glsl"))
            {
                appr_ver = &geom_max_ver;
            }
            else if (!strcmp(&ent->d_name[flen + 3], ".frag.glsl"))
            {
                appr_ver = &frag_max_ver;
            }
            else
            {
                throw 1; // TODO
            }

            if ((file_ver <= this_ver) && (file_ver > *appr_ver))
            {
                *appr_ver = file_ver;
            }
        }
    }

    // Both a vertex shader and a fragment shader are required
    if (!vert_max_ver || !frag_max_ver)
    {
        throw 2; // TODO
    }


    id = glCreateProgram();


    char fname[len + 10];

    sprintf(fname, "%s.%i.vert.glsl", base, vert_max_ver);
    shader vert(fname);

    glAttachShader(id, vert.id);

    sprintf(fname, "%s.%i.frag.glsl", base, frag_max_ver);
    shader frag(fname);

    glAttachShader(id, frag.id);

    if (geom_max_ver)
    {
        sprintf(fname, "%s.%i.geom.glsl", base, geom_max_ver);
        shader geom(fname);

        glAttachShader(id, geom.id);
    }

    glLinkProgram(id);


    int status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (!status)
    {
        glDeleteProgram(id);
        throw 3; // TODO (besides exception: emit error message)
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


void program::set_uniform(int location, int v)
{
    use();

    glUniform1i(location, v);
}
