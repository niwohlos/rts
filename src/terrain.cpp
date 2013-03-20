#include "opengl.hpp"

extern "C"
{
#include <SDL.h>
#include <SDL_image.h>
}

#include <cstdint>

#include "camera.hpp"
#include "terrain.hpp"


static void *load_image(const char *name, int *width, int *height, int bpp)
{
    SDL_Surface *sfc = IMG_Load(name);

    if (!sfc)
    {
        return NULL;
    }

    *width  = sfc->w;
    *height = sfc->h;

    void *buffer = malloc(sfc->w * sfc->h * bpp);

    SDL_LockSurface(sfc);


    uint8_t *out = static_cast<uint8_t *>(buffer);
    const uint8_t *in = static_cast<uint8_t *>(sfc->pixels);

    out += sfc->w * (sfc->h - 1) * bpp;

    int scanline_padding = sfc->pitch - sfc->w * sfc->format->BytesPerPixel;

    if (sfc->format->BytesPerPixel > bpp)
    {
        for (int y = 0; y < sfc->h; y++)
        {
            for (int x = 0; x < sfc->w; x++)
            {
                for (int i = 0; i < bpp; i++)
                {
                    *(out++) = *(in++);
                }

                in += sfc->format->BytesPerPixel - bpp;
            }

            in  += scanline_padding;
            out -= sfc->w * 2 * bpp;
        }
    }
    else if (sfc->format->BytesPerPixel == bpp)
    {
        for (int y = 0; y < sfc->h; y++)
        {
            memcpy(out, in, sfc->w * bpp);
            in  += sfc->pitch;
            out -= sfc->w * bpp;
        }
    }
    else
    {
        for (int y = 0; y < sfc->h; y++)
        {
            for (int x = 0; x < sfc->w; x++)
            {
                int i;

                for (i = 0; i < sfc->format->BytesPerPixel; i++)
                {
                    *(out++) = *(in++);
                }

                for (; i < bpp; i++)
                {
                    *(out++) = 0;
                }
            }

            in  += scanline_padding;
            out -= sfc->w * 2 * bpp;
        }
    }


    SDL_UnlockSurface(sfc);

    SDL_FreeSurface(sfc);


    return buffer;
}


static unsigned load_texture(const char *filename, int channels)
{
    int format;
    switch (channels)
    {
        case 1: format = GL_RED;  break;
        case 2: format = GL_RG;   break;
        case 3: format = GL_RGB;  break;
        case 4: format = GL_RGBA; break;
        default: return 0;
    }


    int w, h;
    void *buffer = load_image(filename, &w, &h, channels);

    if (buffer == NULL)
    {
        return 0;
    }


    unsigned id;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, buffer);

    free(buffer);


    return id;
}


terrain::terrain(const char *height_map)
{
    height_map_gl_id = load_texture(height_map, 1);

    if (!height_map_gl_id)
    {
        throw 42; // TODO
    }


    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, (1 + 512 * 1023) * sizeof(vec2), NULL, GL_STATIC_DRAW);

    vec2 *vertex_data = reinterpret_cast<vec2 *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

    int vtx_index = 0;

    vertex_data[vtx_index++] = vec2(-1.f, 1.f);

    for (int y = 0; y < 512; y++)
    {
        for (int x = 0; x < 512; x++)
        {
            if (y % 2)
            {
                // Even: Left to right

                vertex_data[vtx_index++] = vec2(x / 512.f, 1.f - (y + 1) / 512.f);

                if (x < 511)
                {
                    vertex_data[vtx_index++] = vec2((x + 1) / 512.f, 1.f - y / 512.f);
                }
            }
            else
            {
                // Odd: Right to left

                vertex_data[vtx_index++] = vec2(1.f - x / 512.f, 1.f - (y + 1) / 512.f);

                if (x < 511)
                {
                    vertex_data[vtx_index++] = vec2(1.f - (x + 1) / 512.f, 1.f - y / 512.f);
                }
            }
        }
    }

    vertex_buffer_vertices = vtx_index;

    glUnmapBuffer(GL_ARRAY_BUFFER);


    display_program = new program("data/terrain");

    display_program->set_uniform("height_map", 0);
    display_program_mvp_loc = display_program->get_uniform_location("mvp");
}


terrain::~terrain(void)
{
    glDeleteTextures(1, &height_map_gl_id);

    delete display_program;
}


void terrain::draw(void)
{
    display_program->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, height_map_gl_id);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, reinterpret_cast<void *>(0));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_buffer_vertices);

    glDisableVertexAttribArray(0);
}


void terrain::update_camera(camera *cam)
{
    display_program->set_uniform(display_program_mvp_loc, cam->projection * cam->modelview);
}
