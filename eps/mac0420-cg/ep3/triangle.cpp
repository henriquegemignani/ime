#include "triangle.h"
#include "matrix.h"

Triangle::Triangle(Pigment *p, Surface *s, Vector3D v[]) : Object(p, s) {
	pos[0] = v[0]; pos[1] = v[1]; pos[2] = v[2];
	normal = Vector3D::VectorProduct(pos[1] - pos[0], pos[2] - pos[0]).Normalize();
}

double Triangle::Intersect(Vector3D p, Vector3D u) {
	Vector3D wp = p - pos[0],
			 w1 = pos[1] - pos[0],
			 w2 = pos[2] - pos[0];
	Matrix M = Matrix(-u, w1, w2);
	Vector3D resp = M.Inverse() * wp; // Se M é singular, resp vira (0,0,0)
	if(resp[1] <= 0 || resp[2] <= 0 || resp[1] + resp[2] > 1)
		return NO_COLLISION;
	return resp[0];
}
