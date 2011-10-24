#ifndef OBJECT_H_
#define OBJECT_H_

#include "vector3d.h"
#include "pigment.h"
#include "surface.h"

#define NO_COLLISION -1

class Object {
public:
	Object(Pigment *p, Surface* s) : pig(p), sur(s) {}
	virtual ~Object() {}
	virtual double Intersect(Vector3D p, Vector3D u) { return NO_COLLISION; }
	Vector3D GetColorAt(Vector3D pos) { return pig->GetColorAt(pos); }
	virtual Vector3D Normal(Vector3D pos) { return Vector3D(); }

	const Surface& surface() const { return *sur; }

protected:
	Pigment *pig;
	Surface *sur;
};

#endif /* OBJECT_H_ */
