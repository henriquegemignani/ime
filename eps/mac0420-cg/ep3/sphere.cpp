#include "sphere.h"
#include <cmath>

double Sphere::Intersect(Vector3D p, Vector3D u) {
	Vector3D v = p - pos;
	double delta = pow(v * u, 2) - (v.NormSquared() - r*r);
	if(delta < 0) return -1;
	double t = -(v * u) - sqrt(delta);
	return t;
}

Vector3D Sphere::Normal(Vector3D p) {
	return (p - pos).Normalize();
}
