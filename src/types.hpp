#ifndef TYPES_HPP
#define TYPES_HPP

#include <cmath>
#include <cstring>


class vec4
{
    public:
        vec4(void)
        { x = y = z = w = 0.f; }

        vec4(float xv, float yv, float zv, float wv)
        { x = xv; y = yv; z = zv; w = wv; }


        float operator[](int i) const
        { return d[i]; }

        float &operator[](int i)
        { return d[i]; }


        vec4 operator*(float s) const
        { return vec4(x * s, y * s, z * s, w * s); }

        vec4 operator+(const vec4 &v) const
        { return vec4(x + v.x, y + v.y, z + v.z, w + v.w); }


        union
        {
            struct { float x, y, z, w; };
            struct { float r, g, b, a; };
            struct { float s, t, p, q; };
            float d[4];
        };
};


class vec3
{
    public:
        vec3(void)
        { x = y = z = 0.f; }

        vec3(float xv, float yv, float zv)
        { x = xv; y = yv; z = zv; }


        float length(void)
        { return sqrtf(x * x + y * y + z * z); }


        vec3 normed(void)
        { float len = length(); return vec3(x / len, y / len, z / len); }


        float operator[](int i) const
        { return d[i]; }

        float &operator[](int i)
        { return d[i]; }


        union
        {
            struct { float x, y, z; };
            struct { float r, g, b; };
            struct { float s, t, p; };
            float d[3];
        };
};


class vec2
{
    public:
        vec2(void)
        { x = y = 0.f; }

        vec2(float xv, float yv)
        { x = xv; y = yv; }


        float operator[](int i) const
        { return d[i]; }

        float &operator[](int i)
        { return d[i]; }


        union
        {
            struct { float x, y; };
            struct { float r, g; };
            struct { float s, t; };
            float d[2];
        };
};


class mat4
{
    public:
        mat4(const mat4 &m)
        { memcpy(d, m.d, sizeof(d)); }

        mat4(float d0, float d1, float d2, float d3,
             float d4, float d5, float d6, float d7,
             float d8, float d9, float dA, float dB,
             float dC, float dD, float dE, float dF)
        {
            d[ 0] = d0; d[ 1] = d1; d[ 2] = d2; d[ 3] = d3;
            d[ 4] = d4; d[ 5] = d5; d[ 6] = d6; d[ 7] = d7;
            d[ 8] = d8; d[ 9] = d9; d[10] = dA; d[11] = dB;
            d[12] = dC; d[13] = dD; d[14] = dE; d[15] = dF;
        }

        mat4(const vec4 &c1, const vec4 &c2, const vec4 &c3, const vec4 &c4)
        { memcpy(&d[ 0], c1.d, sizeof(c1.d)); memcpy(&d[ 4], c2.d, sizeof(c2.d)); memcpy(&d[ 8], c3.d, sizeof(c3.d)); memcpy(&d[12], c4.d, sizeof(c4.d)); }


        mat4 &operator*=(const mat4 &m);
        mat4 &translate(const vec3 &v);
        mat4 &rotate(float a, const vec3 &v);
        mat4 &scale(const vec3 &v);

        mat4 operator*(const mat4 &m) const;
        mat4 translated(const vec3 &v) const;
        mat4 rotated(float a, const vec3 &v) const;
        mat4 scaled(const vec3 &v) const;


        float det(void);
        void transposed_invert(void);


        static mat4 identity(void)
        {
            return mat4(1.f, 0.f, 0.f, 0.f,
                        0.f, 1.f, 0.f, 0.f,
                        0.f, 0.f, 1.f, 0.f,
                        0.f, 0.f, 0.f, 1.f);
        }

        static mat4 projection(float fov, float aspect, float zn, float zf)
        {
            return mat4(fov / aspect, 0.f, 0.f, 0.f,
                        0.f, fov, 0.f, 0.f,
                        0.f, 0.f, (zn + zf) / (zn - zf), -1.f,
                        0.f, 0.f, (2.f * zn * zf) / (zn - zf), 0.f);
        }


        float d[16];
};


class mat3
{
    public:
        mat3(const mat3 &m)
        { memcpy(d, m.d, sizeof(d)); }

        mat3(const mat4 &m)
        { memcpy(&d[0], &m.d[0], sizeof(d[0]) * 3); memcpy(&d[3], &m.d[4], sizeof(d[3]) * 3); memcpy(&d[6], &m.d[8], sizeof(d[6]) * 3); }

        mat3(const vec3 &c1, const vec3 &c2, const vec3 &c3)
        { memcpy(&d[0], c1.d, sizeof(c1.d)); memcpy(&d[3], c2.d, sizeof(c2.d)); memcpy(&d[6], c3.d, sizeof(c3.d)); }


        vec3 operator*(const vec3 &v) const;


        float det(void);
        void transposed_invert(void);


        float d[9];
};

#endif
