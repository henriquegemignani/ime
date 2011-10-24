#ifndef SPHERE_H_
#define SPHERE_H_

#include "object.h"
#include "vector3d.h"

class Sphere : public Object {
public:
	Sphere(Pigment *pig, Surface *s, Vector3D p, double radius)
		: Object(pig, s), pos(p), r(radius) {}

	virtual double Intersect(Vector3D p, Vector3D u);
	Vector3D Normal(Vector3D pos);

	Vector3D Center() { return pos; }

protected:
	Vector3D pos;
	double r;
};

#endif
