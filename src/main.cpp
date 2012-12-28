#include <cstdlib>
#include <iostream>

extern "C"
{
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>
}

int main(int argc, char *argv[])
{
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

    SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_DOUBLEBUF);

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
