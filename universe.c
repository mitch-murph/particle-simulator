#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "particle.h"
#include "universe.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define MALLOC_N(d_type, n_elements)    ((d_type*)malloc(sizeof(d_type)*n_elements))
#define MALLOC(d_type)                  ((d_type*)malloc(sizeof(d_type)))

struct Universe* create_universe(size_t num_particles, int width, int height){
    struct Universe* new_universe = MALLOC(struct Universe);
    new_universe->particles = MALLOC_N(struct Particle, num_particles);
    for (int i = 0; i < num_particles; i++){
        new_universe->particles[i].point = MALLOC(struct Point);
        new_universe->particles[i].vel = MALLOC(struct Point);
    }
    new_universe->size = num_particles;
    new_universe->capacity = num_particles;
    new_universe->screen_width = width;
    new_universe->screen_height = height;
    return new_universe;
}

void randomise_universe_rings(struct Universe *universe){
    srand(time(NULL));
    universe->particles[0].point->x = 400;
    universe->particles[0].point->y = 400;
    universe->particles[0].vel->x = 0;
    universe->particles[0].vel->y = 0;
    universe->particles[0].mass = 5;
    for (int i = 1; i < universe->size; i++){
        // double x_pos = rand()%(SCREEN_WIDTH - 400) + 200;
        // double y_pos = rand()%(SCREEN_HEIGHT - 400) + 200;
        // double angle = (rand()%(47))/10+1.5707;
        double angle = (double)(rand()%628318598)/100000000;
        double ra = 400;//(rand()%(int)(sqrt((SCREEN_HEIGHT*SCREEN_HEIGHT)/8)*10000))/10000; // (rand()%3+2)*300/3;
        double x_pos = ra*cos(angle) + 400;
        double y_pos = ra*sin(angle) + 400;
        printf("<%f, %f> %d\n", x_pos, y_pos, i);
        universe->particles[i].point->x = x_pos;
        universe->particles[i].point->y = y_pos;
        if (((int)ra)%200 == 0){
            universe->particles[i].vel->x = -(y_pos-400)/400;
            universe->particles[i].vel->y = (x_pos-400)/400;
        }
        else {
            universe->particles[i].vel->x = (y_pos-400)/400;
            universe->particles[i].vel->y = -(x_pos-400)/400;
        }
        universe->particles[i].mass = 5;
    }
}

void randomise_universe_4star(struct Universe *universe){
    srand(time(NULL));
    universe->particles[0].point->x = 0;
    universe->particles[0].point->y = 400;
    universe->particles[0].vel->x = 0;
    universe->particles[0].vel->y = -4;
    universe->particles[0].mass = 20;
    universe->particles[1].point->x = 400;
    universe->particles[1].point->y = 800;
    universe->particles[1].vel->x = -4;
    universe->particles[1].vel->y = 0;
    universe->particles[1].mass = 20;
    universe->particles[2].point->x = 800;
    universe->particles[2].point->y = 400;
    universe->particles[2].vel->x = 0;
    universe->particles[2].vel->y = 4;
    universe->particles[2].mass = 20;
    universe->particles[3].point->x = 400;
    universe->particles[3].point->y = 0;
    universe->particles[3].vel->x = 4;
    universe->particles[3].vel->y = 0;
    universe->particles[3].mass = 20;
    universe->particles[4].point->x = 400;
    universe->particles[4].point->y = 400;
    universe->particles[4].vel->x = 0;
    universe->particles[4].vel->y = 0;
    universe->particles[4].mass = 50;
}

void randomise_universe_2star(struct Universe *universe){
    srand(time(NULL));
    universe->particles[0].point->x = 250;
    universe->particles[0].point->y = 400;
    universe->particles[0].vel->x = 0;
    universe->particles[0].vel->y = -3;
    universe->particles[0].mass = 20;
    universe->particles[1].point->x = 550;
    universe->particles[1].point->y = 400;
    universe->particles[1].vel->x = 0;
    universe->particles[1].vel->y = 3;
    universe->particles[1].mass = 20;
}

void randomise_universe(struct Universe *universe){
    srand(time(NULL));
    for (int i = 0; i < universe->size; i++){
        double x_pos = rand()%(SCREEN_WIDTH - 300) + 150;
        double y_pos = rand()%(SCREEN_HEIGHT - 300) + 150;
        universe->particles[i].point->x = x_pos;
        universe->particles[i].point->y = y_pos;
        universe->particles[i].vel->x = 0;
        universe->particles[i].vel->y = 0;
        universe->particles[i].mass = 1;
    }
}

void update_universe(struct Universe *universe){
    compute(universe->particles, &universe->size);
    apply_velocity(universe->particles, universe->size);
}

void insert_particle(struct Universe *universe, int x, int y, double v_x, double v_y, int size){
    int i = universe->size;
    universe->size++;
    struct Particle *old_particles = universe->particles;
    struct Particle *new_particles = MALLOC_N(struct Particle, universe->size);
    for (int j = 0; j < universe->size; j++){
        new_particles[j] = universe->particles[j];
    }
    free(old_particles);
    universe->particles = new_particles;
    universe->particles[i].point = MALLOC(struct Point);
    universe->particles[i].vel = MALLOC(struct Point);
    universe->particles[i].point->x = x;
    universe->particles[i].point->y = y;
    universe->particles[i].vel->x = v_x/20;
    universe->particles[i].vel->y = v_y/20;
    universe->particles[i].mass = size;
}