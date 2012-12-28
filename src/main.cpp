#include <cstdlib>
#include <iostream>
#include <cstring>

extern "C"
{
#include <GL/gl.h>
#include <SDL.h>
#include <lua.h>
#include <lauxlib.h>
#include <unistd.h>
}


int main(int argc, char *argv[])
{
    int c;
    int width = 800, height = 600;

    while ((c = getopt(argc, argv, "vw:h:")) != -1) {
        switch (c) {
            case 'w':
                width = atoi(optarg);
                std::cout << "Using a width of " << width << " pixel" << std::endl;
                break;
            case 'h':
                height = atoi(optarg);
                std::cout << "Using a height of " << height << " pixel" << std::endl;
                break;
            case 'v':
                std::cout << "0" << std::endl;
                return EXIT_SUCCESS;
                break;
            default:
                break;
        }
    }

    lua_State *L = luaL_newstate();

    if (!L)
    {
        std::cerr << "Unable to inititalize Lua" << std::endl;

        return EXIT_FAILURE;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;

        return EXIT_FAILURE;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_DOUBLEBUF);

    bool quit = false;

    while (!quit)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.5f, -0.5f);
        glEnd();

        SDL_GL_SwapBuffers();

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    SDL_Quit();
    lua_close(L);

    return EXIT_SUCCESS;
}
