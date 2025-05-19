#include "orbital_body.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

const double G = 1;

double abs_distance(Body* b1, Body* b2) {
    double dx = b2->position.x - b1->position.x;
    double dy = b2->position.y - b1->position.y;
    double dz = b2->position.z - b1->position.z;

    return sqrt(dx*dx + dy*dy + dz*dz);
}

Vector3 unit_vector_given_distance(Body* b1, Body* b2, double distance) {
    Vector3 vec;
    vec.x = (b2->position.x - b1->position.x) / distance;
    vec.y = (b2->position.y - b1->position.y) / distance;
    vec.z = (b2->position.z - b1->position.z) / distance;

    return vec;
}

Vector3 grav_force_vect_between_two_bodies(Body* b1, Body* b2) {
    Vector3 force_vector;

    double r = abs_distance(b1, b2);
    if (r == 0) {
        force_vector.x = 0;
        force_vector.y = 0;
        force_vector.z = 0;
        return force_vector; // Avoid division by zero
    }
    double abs_force = G * b1->mass * b2->mass / (r*r); // Newton's law of gravitation: (G * m1 * m2 / r^2) is magnitude of force

    Vector3 r_unit = unit_vector_given_distance(b1, b2, r);
    force_vector.x = abs_force * r_unit.x;
    force_vector.y = abs_force * r_unit.y;
    force_vector.z = abs_force * r_unit.z;

    return force_vector;
}

Vector3 acceleration_vector(Body* b1, Vector3 force) {
    Vector3 acc;
    acc.x = force.x / b1->mass;
    acc.y = force.y / b1->mass;
    acc.z = force.z / b1->mass;

    return acc;
}

void update_body(Body* body, Vector3 acceleration, double dt) {
    // Update the velocity of the body
    // using the acceleration vector and the time difference
    body->velocity.x = body->velocity.x + (acceleration.x * dt);
    body->velocity.y = body->velocity.y + (acceleration.y * dt);
    body->velocity.z = body->velocity.z + (acceleration.z * dt);
    // Update the position of the body
    // using the velocity vector and the time difference
    body->position.x = body->position.x + (body->velocity.x * dt);
    body->position.y = body->position.y + (body->velocity.y * dt);
    body->position.z = body->position.z + (body->velocity.z * dt);
}

void generate_bodies(int num_bodies, Body* bodies) {
    for (int i = 0; i < num_bodies; i++) {
        snprintf(bodies[i].name, sizeof(bodies[i].name), "Body %d", i);
        bodies[i].mass = (double)(rand() % 100);
        bodies[i].position = (Vector3){ (double)(rand() % (100 - (-100) + 1) + (-100)), (double)(rand() % (100 - (-100) + 1) + (-100)), (double)(rand() % (100 - (-100) + 1) + (-100)) };
        bodies[i].velocity = (Vector3){ (double)(rand() % (5 - (-5) + 1) + (-5)), (double)(rand() % (5 - (-5) + 1) + (-5)), (double)(rand() % (5 - (-5) + 1) + (-5)) };
        bodies[i].radius = (double)(rand() % 15);
        bodies[i].color = (Color) { rand() % 256, rand() % 256, rand() % 256, 255 };
    }
}