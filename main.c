#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


struct Particle;

struct Universe {
    struct Particle* particles;
    size_t size;
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
    double G = 10;
    double f = (G * a.mass * b.mass)/distance_sq(a.point, b.point);
    double angle = 0;
    if (a.point.y-b.point.y != 0)
        angle = atan((a.point.x-b.point.x)/(a.point.y-b.point.y));
    return (struct Point){
       f*cos(angle), 
       f*sin(angle), 
    };
}

void compute(struct Particle list[], int n){
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            struct Point f = force(list[i], list[j]);
            list[i].vel.x += -f.x/list[i].mass;
            list[i].vel.y += -f.y/list[i].mass;
            list[j].vel.x += f.x/list[i].mass;
            list[j].vel.y += f.y/list[i].mass;
        }
    }
}

void progress(struct Particle list[], int n){
    for (int i = 0; i < n; i++){
        list[i].point.x += list[i].vel.x;
        list[i].point.y += list[i].vel.y;
    }
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    srand(time(NULL));

   int num = 20;

    struct Particle particles[num];
    for (int i = 0; i < num; i++){
        particles[i] = (struct Particle){
            (struct Point){
                rand()%screenWidth + 1,
                rand()%screenHeight + 1
            },
            (struct Point){
                0,
                0
            },
            rand()%25+1,
        };
        printf("<%f, %f>\n", particles[i].point.x, particles[i].point.y);
    }


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {

        BeginDrawing();

            ClearBackground(RAYWHITE);

            for (int i = 0; i < num; i++){
               DrawCircle(particles[i].point.x, particles[i].point.y, particles[i].mass, DARKBLUE);
            }
            compute(particles, num);
            progress(particles, num);

        EndDrawing();
    }

    
    CloseWindow();

    return 0;
}
