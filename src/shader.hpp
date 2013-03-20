#ifndef SHADER_HPP
#define SHADER_HPP

#include <cstddef>
#include <cstdint>
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
        program(const char *base);
        ~program(void);

        void use(void);

        int get_uniform_location(const char *name);

        void set_uniform(int location, const mat4 &m);
        void set_uniform(int location, const mat3 &m);
        void set_uniform(int location, const vec3 &v);
        void set_uniform(int location, int v);

        template<typename T> void set_uniform(const char *name, const T &v)
        { set_uniform(get_uniform_location(name), v); }


        unsigned id;
};

#endif
