#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Point{
    double x;
    double y;
};

struct Particle {
    struct Point point;
    struct Point vel;
    double mass;
};

double normalise(double value){
    value /=10;
    return exp(value)/(1+exp(value));
}

double distance(struct Point a, struct Point b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

struct Point sum_x(struct Particle list[], int n){
    struct Point new_vel = {0,0};
    for (int i = 0; i < n; i++){

    }
    return new_vel;
}

int main(){
    struct Particle list[2];
    // list[0] = (struct Particle) {0, 0, 0, 0, 10};
    // list[1] = (struct Particle) {1, 1, 0, 0, 1};
    int new_a_x;
    printf("%f", distance((struct Point){0, 0}, (struct Point){3, 4})));
    return 0;
}