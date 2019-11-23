#include <stdlib.h>
#include <math.h>
#include "particle.h"

double calc_distance_sq(struct Point a, struct Point b){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

struct Point calc_gravity(struct Particle a, struct Particle b){
    double distance = calc_distance_sq(*a.point, *b.point);
    double G = 1;
    double nomi = (G * a.mass * b.mass);
    return (struct Point){
       (a.point->x - b.point->x) * nomi/distance,
       (a.point->y - b.point->y) * nomi/distance 
    };
}

void apply_force(struct Particle particle, struct Point force, double direction){
    particle.vel->x += direction*force.x/particle.mass;
    particle.vel->y += direction*force.y/particle.mass;
}

void apply_momentum(struct Particle *a, struct Particle b)
    {double total_mass = sqrt(a->mass*a->mass + b.mass*b.mass);
    a->vel->x = (a->vel->x*a->mass + b.vel->x*b.mass)/total_mass;
    a->vel->y = (a->vel->y*a->mass + b.vel->y*b.mass)/total_mass;
    a->mass = total_mass;
}

void compute(struct Particle *list, size_t *size){
    int shift;
    for (int i = 0; i < *size; i++){                        // Loop through the
        shift = 0;                                          // permutations of
        for (int j = i + 1; j < *size; j++){                // two particles

            list[j] = list[j+shift];                        // Overwrite merged particles

            struct Point force = calc_gravity(list[i], list[j]);
            apply_force(list[i], force, -1);                // apply the equate forces
            apply_force(list[j], force, 1);                 // of gravity to the particles

            double distance_sq = calc_distance_sq(*list[i].point, *list[j].point);
            double total_width = (list[i].mass + list[j].mass);
            if (distance_sq < total_width*total_width){     // Check if the particles are overlapping
                if (list[i].mass < list[j].mass){
                    list[i].point->x = list[j].point->x;    // Force the larger particle 
                    list[i].point->y = list[j].point->y;    // to hold position
                }

                apply_momentum(&list[i], list[j]);

                j--;                                        // Adjust the shift to
                shift++;                                    // overwrite merged particles
                (*size)--;                                  // and reduce to the new size
            }
        }
    }
}

void apply_velocity(struct Particle list[], int n){
    for (int i = 0; i < n; i++){
        list[i].point->x += list[i].vel->x;
        list[i].point->y += list[i].vel->y;
    }
}