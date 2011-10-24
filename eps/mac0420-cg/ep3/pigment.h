#ifndef PIGMENT_H_
#define PIGMENT_H_

#include "vector3d.h"

class Pigment {
public:
	Pigment(Vector3D color) : simple(true), color1(color) {}
	Pigment(Vector3D colora, Vector3D colorb, double S)
		: simple(false), color1(colora), color2(colorb), s(S) {}
	virtual ~Pigment() {}

	Vector3D GetColorAt(double x, double y, double z) const;
	Vector3D GetColorAt(Vector3D pos) const {
		return GetColorAt(pos.x, pos.y, pos.z);
	}
	Vector3D operator() (double x, double y, double z) const { return GetColorAt(x, y, z); }
	Vector3D operator() (Vector3D pos) const { return GetColorAt(pos); }

private:
	bool simple;
	Vector3D color1, color2;
	double s;
};

#endif /* PIGMENT_H_ */
