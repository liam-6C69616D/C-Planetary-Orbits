#include "../include/orbital_body.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

double abs_distance(Body* b1, Body* b2) {
    double dx = b1->x - b2->x;
    double dy = b1->y - b2->y;
    double dz = b1->z - b2->z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

double* distance_vector(Body* b1, Body* b2) {
    double* vec = (double*) malloc (3 * sizeof(double));
    double distance = abs_distance(b1, b2);
    vec[0] = abs(b1->x - b2->x) / distance;
    vec[1] = abs(b1->y - b2->y) / distance;
    vec[2] = abs(b1->z - b2->z) / distance;
    return vec;
}

double* gravitational_force_vector(Body* b1, Body* b2) {
    double r = abs_distance(b1, b2);
    double abs_force = G * b1->mass * b2->mass / (r*r);
    printf("b1->mass: %f\n", b1->mass);
    double* vec = distance_vector(b1, b2);
    double force_x = abs_force * vec[0];
    double force_y = abs_force * vec[1];
    double force_z = abs_force * vec[2];
    free(vec);
    double* force = (double*) malloc (3 * sizeof(double));
    force[0] = force_x;
    force[1] = force_y;
    force[2] = force_z;
    return force;
}

double* acceleration_vector(Body* b1, Body* b2) {
    double* force = gravitational_force_vector(b1, b2);
    double* acc = (double*) malloc (3 * sizeof(double));
    acc[0] = force[0] / b1->mass;
    acc[1] = force[1] / b1->mass;
    acc[2] = force[2] / b1->mass;
    free(force);
    return acc;
}

void calculate_and_set_velocities_and_positions(Body* b1, Body* b2, double dt) {
    double* acc = acceleration_vector(b1, b2);
    b1->vx += acc[0] * dt;
    b1->vy += acc[1] * dt;
    b1->vz += acc[2] * dt;
    free(acc);
    b1->x += b1->vx * dt;
    b1->y += b1->vy * dt;
    b1->z += b1->vz * dt;
}

// int main() {
//     Body b1 = {5e24, 0, 0, 0, 0, 5e3, 0, 2.44e6, "b1"};
//     Body b2 = {6e24, 1.5e11, 0, 0, 0, 3e4, 0, 3.39e6, "b2"};

//     double dt = 0;
//     while (true) {
//         calculate_and_set_velocities_and_positions(&b1, &b2, dt);
//         printf("dt: %f\n", dt);
//         printf("b1: %f %f %f\n", b1.x, b1.y, b1.z);
//         printf("b2: %f %f %f\n", b2.x, b2.y, b2.z);
//         printf("\n\n");
//         dt += 1;
//         sleep(1);
//     }
// }