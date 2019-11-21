#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MALLOC_N(d_type, n_elements)    ((d_type*)malloc(sizeof(d_type)*n_elements))
#define MALLOC(d_type)                  ((d_type*)malloc(sizeof(d_type)))
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

struct Particle;

struct Universe {
    struct Particle* particles;
    size_t size;
    size_t capacity;
    size_t permanent_index;
};

struct Point{
    double x;
    double y;
};

struct Particle {
    struct Point point;
    struct Point vel;
    double mass;
};

double normalise(double x){
    return x/(1+x);
}

double ratio(int a, int b){
    return (a*b)/max(a,b);
}

double distance_sq(struct Point a, struct Point b){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}


struct Point force(struct Particle a, struct Particle b){
    double distance = distance_sq(a.point, b.point);
    double G = 0.001;
    double nomi = (G * a.mass * b.mass);
    return (struct Point){
       (a.point.x - b.point.x) * nomi/distance,
       (a.point.y - b.point.y) * nomi/distance 
    };
}

int overlap(struct Particle a, struct Particle b){
    return (a.point.x + a.mass > b.point.x - b.mass && a.point.x - a.mass < b.point.x + a.mass);
}

void print_universe(struct Universe universe){
    for (int i = 0; i < universe.size; i++){
        printf("-> %d %f\n", i, universe.particles[i].mass);
    }
    printf("\n");
}

void compute(struct Universe *universe){
    struct Particle *list = universe->particles;
    int shift = 0;
    int i = 0, j = 0;
    while (i < universe->size){
        j = i + 1;
        shift = 0;
        while (j < universe->size){
            list[j] = list[j+shift];

            struct Point f = force(list[i], list[j]);
            list[i].vel.x += -f.x/list[i].mass;
            list[i].vel.y += -f.y/list[i].mass;
            list[j].vel.x += f.x/list[i].mass;
            list[j].vel.y += f.y/list[i].mass;

            double distance = distance_sq(list[i].point, list[j].point);
            double total_width_sq = (list[i].mass + list[j].mass);
            total_width_sq *= total_width_sq;
            if (distance < total_width_sq){
                list[i].mass += (list[j].mass)/3.14;
                j--;
                shift++;
                universe->size--;
            }

            j++;
        }
        i++;
    }
}

void progress(struct Particle list[], int n){
    for (int i = 0; i < n; i++){
        list[i].point.x += list[i].vel.x;
        list[i].point.y += list[i].vel.y;
    }
}

struct Universe* build_universe(size_t num_particles){
    struct Universe* new_universe = MALLOC(struct Universe);
    new_universe->particles = MALLOC_N(struct Particle, num_particles);
    new_universe->size = num_particles;
    new_universe->capacity = num_particles;
    return new_universe;
}

void randomise_universe(struct Universe universe){

    for (int i = 0; i < universe.size; i++){
        universe.particles[i] = (struct Particle){
            (struct Point){
                rand()%(SCREEN_WIDTH - 200) + 100,
                rand()%(SCREEN_HEIGHT - 200) + 100
            },
            (struct Point){
                0,
                0
            },
            //rand()%25+1,
            3
        };
    }
}

int main()
{

    srand(time(NULL));

    struct Universe* universe = build_universe(20);
    randomise_universe(*universe);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Simulator");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {

        BeginDrawing();

            ClearBackground(RAYWHITE);
            for (int i = 0; i < universe->size; i++){
                DrawCircle(universe->particles[i].point.x, universe->particles[i].point.y, universe->particles[i].mass, DARKBLUE);
            }
            compute(universe);
            progress(universe->particles, universe->size);

        EndDrawing();
    }

    
    CloseWindow();

    return 0;
}