#ifndef SEACRAFT_SIMULATION_GEOOMETRY_H
#define SEACRAFT_SIMULATION_GEOOMETRY_H

#include <iostream>
#include <iomanip>
using namespace std;
// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);


// class declarations
typedef struct Point {
	double x;
	double y;
	Point(double x, double y);
	Point();
	void print() const;
	string toString() const;
	bool operator==(const Point& rhs);
} Point;


struct Polar_vector;

typedef struct Cartesian_vector {
    explicit Cartesian_vector(const struct Polar_vector & pv);
	Cartesian_vector();
	void operator=(const struct Polar_vector & pv);
	double delta_x;
	double delta_y;
} Cartesian_vector;


typedef struct Polar_vector {
    explicit Polar_vector(const Cartesian_vector & cv);
	Polar_vector();
	void operator=(const Cartesian_vector & cv);
	double r;
	double theta;
} Polar_vector;

double square(double d);

#endif