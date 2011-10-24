#ifndef LIGHT_H_
#define LIGHT_H_

#include "vector3d.h"

class Light {
public:
	Light(Vector3D position, Vector3D color, Vector3D abc)
		: pos(position), rgb(color), atenuation(abc) {}

	Vector3D Position() const { return pos; }
	Vector3D GetColorAt(Vector3D location);
	Vector3D Color() const { return rgb; }

protected:
	Vector3D pos, rgb, atenuation;
};

#endif
