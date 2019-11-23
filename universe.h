#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <stdlib.h>

struct Universe {
    struct Particle* particles;
    size_t size;
    size_t capacity;
    size_t permanent_index;
    int screen_width;
    int screen_height;
};

struct Universe* create_universe(size_t num_particles, int width, int height);

void randomise_universe(struct Universe *universe);

void update_universe(struct Universe *universe);

void insert_particle(struct Universe *universe, int x, int y, double v_x, double v_y, int size);

#endif