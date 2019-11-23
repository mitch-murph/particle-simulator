#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>

struct Point{
    double x;
    double y;
};

struct Particle {
    struct Point* point;
    struct Point* vel;
    double mass;
};

double calc_distance_sq(struct Point a, struct Point b);

struct Point calc_gravity(struct Particle a, struct Particle b);

void apply_force(struct Particle particle, struct Point force, double direction);

void apply_momentum(struct Particle *a, struct Particle b);

void compute(struct Particle *list, size_t *size);

void apply_velocity(struct Particle list[], int n);

#endif