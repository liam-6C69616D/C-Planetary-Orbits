#include "orbital_body.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUMBER_OF_BODIES 20

int main(void) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Orbits");

    srand(time(NULL));

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 500.0f, 10.0f }; // Adjusted camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Body *bodies = (Body *) malloc(sizeof(Body) * NUMBER_OF_BODIES);
    generate_bodies(NUMBER_OF_BODIES, bodies);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground((Color) { 0, 0, 0, 255 });

            BeginMode3D(camera);

                for (int i = 0; i < NUMBER_OF_BODIES; i++) {
                    DrawSphere(bodies[i].position, bodies[i].radius, bodies[i].color);
                }
                
                for (int i = 0; i < NUMBER_OF_BODIES; i++) {
                    Vector3 overall_force = { 0, 0, 0 };
                    for (int j = i+1; j < NUMBER_OF_BODIES; j++) {
                        Vector3 force = grav_force_vect_between_two_bodies(&(bodies[i]), &(bodies[j]));
                        overall_force.x += force.x;
                        overall_force.y += force.y;
                        overall_force.z += force.z;
                    }
                    Vector3 acc = acceleration_vector(&bodies[i], overall_force);
                    update_body(&bodies[i], acc, 0.016f);
                }


            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}