#include "orbital_body.h"

int main(void) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Orbits");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f }; // Adjusted camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Body planet1 = { 1.0f, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 2.0f, "Earth" };
    Body planet2 = { 0.5f, {5.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.5f, "Moon" };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground((Color) { 0, 0, 0, 255 });

            BeginMode3D(camera);

                DrawSphereEx(planet1.position, planet1.radius, 100, 100, RED);
                DrawSphere(planet2.position, planet2.radius, BLUE);

                Vector3 force = grav_force_vect_between_two_bodies(&planet1, &planet2);
                
                Vector3 acc1 = acceleration_vector(&planet1, (Vector3){-force.x, -force.y, -force.z});
                Vector3 acc2 = acceleration_vector(&planet2, force);

                update_body(&planet1, acc1, 0.016f);
                update_body(&planet2, acc2, 0.016f);


            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}