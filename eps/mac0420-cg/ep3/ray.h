#ifndef RAY_H_
#define RAY_H_

#include "vector3d.h"
#include "common.h"
#include "object.h"

class Ray {
public:
	Ray(Vector3D orig, Vector3D dir) : source(orig), direction(dir) {}
	virtual ~Ray() {}

	typedef struct {
		Object* obj;
		float dist;
	} Intersection;

	Intersection FindClosestIntersection(Environment &env);

	Vector3D Trace(Environment &env, int recursion = 0);

	const static int MAX_RECURSION = 5;

protected:
	Vector3D LightTrace(Vector3D position, Vector3D normal, Environment &env, int recursion = 0);
	Vector3D OffsetSource() { return source + 1.0e-4 * direction; }
	Vector3D Refract(Intersection &inter, Environment &env, int recursion = 0);

	double Intersect(Object *obj);
	Vector3D source, direction;
	double ior;

};

#endif /* RAY_H_ */
