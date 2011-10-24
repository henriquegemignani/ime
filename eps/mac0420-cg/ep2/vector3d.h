#ifndef VECTOR3D_H_
#define VECTOR3D_H_

class Vector3D {
public:
	Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	float x, y, z;
};

Vector3D operator+(const Vector3D& left_value, const Vector3D& right_value);
Vector3D operator-(const Vector3D& left_value, const Vector3D& right_value);
Vector3D operator*(const Vector3D& left_value, const float& scalar);

#endif
