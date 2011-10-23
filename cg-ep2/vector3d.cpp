#include "vector3d.h"

// Definicao de operacoes de adicao e subtracao com vetores
// e multiplicacao por escalar
Vector3D operator+(const Vector3D& left_value,
                   const Vector3D& right_value) {
    return Vector3D(left_value.x + right_value.x, 
					left_value.y + right_value.y,
					left_value.z + right_value.z);
}
Vector3D operator-(const Vector3D& left_value,
				   const Vector3D& right_value) {
    return Vector3D(left_value.x - right_value.x, 
					left_value.y - right_value.y,
					left_value.z - right_value.z);
}
Vector3D operator*(const Vector3D& left_value,
               const float& scalar) {
    return Vector3D(left_value.x * scalar, left_value.y * scalar, left_value.z * scalar);
}
