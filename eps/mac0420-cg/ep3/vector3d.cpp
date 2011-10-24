#include "vector3d.h"
#include <cmath>

#define n 3

std::istream& operator>> (std::istream& io, Vector3D& v) {
	return io >> v.x >> v.y >> v.z;
}

std::ostream& operator<< (std::ostream& io, Vector3D& v) {
	return io << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

Vector3D operator+(const Vector3D& l, const Vector3D& r) {
    return Vector3D(l[0] + r[0], l[1] + r[1], l[2] + r[2]);
}

Vector3D operator-(const Vector3D& l, const Vector3D& r) {
    return Vector3D(l[0] - r[0], l[1] - r[1], l[2] - r[2]);
}

Vector3D operator-(const Vector3D& v) { return Vector3D(-v[0], -v[1], -v[2]); }

// inner product
double operator*(const Vector3D& l, const Vector3D& r) {
	double resp = 0;
	for(int i = 0; i < n; i++)
		resp += l[i] * r[i];
	return resp;
}

Vector3D operator*(const Vector3D& l, const double& scalar) {
    return Vector3D(l[0] * scalar, l[1] * scalar, l[2] * scalar);
}
Vector3D operator*(const double& scalar, const Vector3D& r) {
	return r * scalar;
}

Vector3D operator/(const Vector3D& l, const double& scalar) {
	return Vector3D(l[0] / scalar, l[1] / scalar, l[2] / scalar);
}

void Vector3D::Dump(FILE* out) {
	fprintf(out, "(%.4f, %.4f, %.4f)", x, y, z);
}

Vector3D Vector3D::Normalize() {
	double norm = Norm();
	return Vector3D(x/norm, y/norm, z/norm);
}

double Vector3D::Norm() {
	return sqrt(NormSquared());
}
double Vector3D::NormSquared() {
	return x*x + y*y + z*z;
}

double& Vector3D::operator[](const int i) { return val[i]; }
double Vector3D::operator[](const int i) const { return val[i]; }

Vector3D Vector3D::VectorProduct(const Vector3D& a, const Vector3D& b) {
    //a × b = [a1b2 − a2b1, a2b0 − a0b2, a0b1 − a1b0].
	return Vector3D(a[1] * b[2] - a[2] * b[1],
					a[2] * b[0] - a[0] * b[2],
					a[0] * b[1] - a[1] * b[0]);
}
