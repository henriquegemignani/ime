#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <cstdio>
#include <iostream>

#define DEBUG Debug::debug()

class Debug {
public:
	static bool debug(bool toggle = false) {
		static bool active = false;
		if(toggle) active = !active;
		return active;
	}
};

class Vector3D {
public:
	Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
	union {
		struct { double x, y, z; };
		struct { double r, g, b; };
		struct { double val[3]; };
	};
	
	void Dump(FILE* out);
	friend std::istream& operator>> (std::istream& i, Vector3D& v);
	friend std::ostream& operator<< (std::ostream& i, Vector3D& v);

	double& operator[](const int i);
	double operator[](const int i) const;
	Vector3D Normalize();
	double Norm();
	double NormSquared();

	static Vector3D VectorProduct(const Vector3D& l, const Vector3D& r);
};

Vector3D operator+(const Vector3D& left_value, const Vector3D& right_value);
Vector3D operator-(const Vector3D& left_value, const Vector3D& right_value);
Vector3D operator-(const Vector3D& value);
double operator*(const Vector3D& left_value, const Vector3D& right_value); // inner product
Vector3D operator*(const Vector3D& left_value, const double& scalar);
Vector3D operator*(const double& scalar, const Vector3D& right_value);
Vector3D operator/(const Vector3D& left_value, const double& scalar);

#endif
