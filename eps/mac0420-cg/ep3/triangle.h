#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "object.h"
#include "vector3d.h"

class Triangle : public Object {
public:
	Triangle(Pigment *p, Surface *s, Vector3D v[]);

	virtual double Intersect(Vector3D p, Vector3D u);
	Vector3D Normal(Vector3D pos) { return normal; }
protected:
	Vector3D pos[3];
	Vector3D normal;
};

#endif
