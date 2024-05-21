/* TYPES */
typedef struct {
    double mass;
    double x,y,z; // position
    double vx,vy,vz; // velocity
    double radius;
    char name[16];
} Body;

const double G = 6.67430e-11; // m^3 kg^-1 s^-2

/* FUNCTION STUBS */
double abs_distance(Body* b1, Body* b2);
double* distance_vector(Body* b1, Body* b2);
// Calculate the gravitational force vector of b1 due to b2
double* gravitational_force_vector(Body* b1, Body* b2);
// Calculate the acceleration vector of b1 due to b2
double* acceleration_vector(Body* b1, Body* b2);
// Calculate the new velocities and positions of b1 due to b2 at time difference dt
void calculate_and_set_velocities_and_positions(Body* b1, Body* b2, double dt);