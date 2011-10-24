/*
 * Vector2D.cpp
 *
 *  Created on: 04/04/2011
 *      Author: Henrique
 */
#include "Vector2D.h"
#include <cmath>

float Vector2D::length() {
	return sqrt(x*x + y*y);
}
float Vector2D::normOne() {
	return fabs(x + y);
}

Vector2D operator+(const Vector2D& left_value,
                   const Vector2D& right_value) {
    return Vector2D(left_value.x + right_value.x, left_value.y + right_value.y);
}
Vector2D operator-(const Vector2D& left_value,
               const Vector2D& right_value) {
    return Vector2D(left_value.x - right_value.x, left_value.y - right_value.y);
}
Vector2D operator*(const Vector2D& left_value,
               const float& scalar) {
    return Vector2D(left_value.x * scalar, left_value.y * scalar);
}
