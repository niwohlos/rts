#ifndef TERRAIN_HPP
#define TERRAIN_HPP

class terrain
{
    public:
        terrain(const char *height_map);
        ~terrain(void);


    private:
        unsigned height_map_gl_id;
};

#endif
