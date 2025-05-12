#ifndef ORBITS_ORBITAL_BODY_H
#define ORBITS_ORBITAL_BODY_H
#include <raylib.h>

typedef struct {
    double mass;
    Vector3 position;
    Vector3 velocity;
    double radius;
    char name[16];
} Body;

extern const double G; // m^3 kg^-1 s^-2

// Euclidean distance between two bodies
double abs_distance(Body* b1, Body* b2);

// Calculate the unit vector between two bodies given their absolute distance
// The unit vector is a vector with a magnitude of 1, used to indicate direction of force
Vector3 unit_vector_given_distance(Body* b1, Body* b2, double distance);

// Calculate the gravitational force vector between b1 and b2
// using Newton's law of gravitation: F = ((G * m1 * m2) / r^2) * r_unit
Vector3 grav_force_vect_between_two_bodies(Body* b1, Body* b2);

// Calculate the acceleration vector of b1 due to the force vector
// using Newton's second law: F = m * a => a = F / m
Vector3 acceleration_vector(Body* b1, Vector3 force);

// Calculate the new velocities and positions of b1 due to b2 at time difference dt
void update_body(Body* body, Vector3 acceleration, double dt);

#endif