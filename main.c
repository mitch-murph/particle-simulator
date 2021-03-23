#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "particle.h"
#include "universe.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int main(){
    struct Universe* universe = create_universe(0, SCREEN_WIDTH, SCREEN_HEIGHT);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Simulator");
    SetTargetFPS(30);
    ClearBackground(RAYWHITE);

    int init_x, init_y, size;

    while (!WindowShouldClose()){
        BeginDrawing();

            ClearBackground(RAYWHITE);
            update_universe(universe);

            if (IsMouseButtonPressed(0)){
                init_x = GetMouseX();
                init_y = GetMouseY();
                size = 1;
            } else if (IsMouseButtonDown(0)){
                if (init_x == GetMouseX() && init_y == GetMouseY()) size+= 1;
                DrawCircle(init_x, init_y, size, BLACK);
                DrawLine(init_x, init_y, GetMouseX(), GetMouseY(), BLACK);
            } else if (IsMouseButtonReleased(0)){
                insert_particle(universe, init_x, init_y, (GetMouseX() - init_x), (GetMouseY() - init_y), size);
            }
            
            for (int i = 0; i < universe->size; i++){
                DrawCircle(universe->particles[i].point->x, universe->particles[i].point->y, universe->particles[i].mass, DARKBLUE);
            }

        EndDrawing();
    }
    CloseWindow();
    free_universe(universe);
    return 0;
}