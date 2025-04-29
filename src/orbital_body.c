#include "orbital_body.h"
#include <math.h>

double abs_distance(Body* b1, Body* b2) {
    double dx = b1->position.x - b2->position.x;
    double dy = b1->position.y - b2->position.y;
    double dz = b1->position.z - b2->position.z;

    return sqrt(dx*dx + dy*dy + dz*dz);
}

Vector3 unit_vector_given_distance(Body* b1, Body* b2, double distance) {
    Vector3 vec;
    vec.x = (b1->position.x - b2->position.x) / distance;
    vec.y = (b1->position.y - b2->position.y) / distance;
    vec.z = (b1->position.z - b2->position.z) / distance;

    return vec;
}

Vector3 grav_force_vect_between_two_bodies(Body* b1, Body* b2) {
    Vector3 force_vector;

    double r = abs_distance(b1, b2);
    double abs_force = G * b1->mass * b2->mass / (r*r); // Newton's law of gravitation (G * m1 * m2 / r^2) is magnitude of force

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