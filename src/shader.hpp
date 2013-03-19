#ifndef SHADER_HPP
#define SHADER_HPP

#include <initializer_list>

#include "types.hpp"


class shader
{
    public:
        shader(const char *file);
        ~shader(void);


        unsigned id;
};


class program
{
    public:
        program(std::initializer_list<const shader *> shaders);
        ~program(void);

        void use(void);

        int get_uniform_location(const char *name);

        void set_uniform(int location, const mat4 &m);


        unsigned id;
};

#endif
