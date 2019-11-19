#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

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
    double G = 1;
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
            list[i].vel.x += f.x/list[i].mass;
            list[i].vel.y += f.y/list[i].mass;
            list[j].vel.x += -f.x/list[i].mass;
            list[j].vel.y += -f.y/list[i].mass;
        }
    }
}

int main(){
    srand(time(NULL));

    struct Particle particles[10];
    for (int i = 0; i < 2; i++){
        particles[i] = (struct Particle){
            (struct Point){
                rand()%2 + 1,
                rand()%2 + 1
            },
            (struct Point){
                0,
                0
            },
            1,
            // (rand()%10) + 1,
        };
        printf("<%f, %f>\n", particles[i].point.x, particles[i].point.y);
    }

    printf("\n\nCOMPUTE\n\n");
    compute(particles, 10);

    for (int i = 0; i < 2; i++){
        printf("<%f, %f>\n", particles[i].vel.x, particles[i].vel.y);
    }


    return 0;
}