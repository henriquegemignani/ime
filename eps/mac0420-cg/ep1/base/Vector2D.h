/*
 * Vector2D.h
 *
 *  Created on: 31/03/2011
 *      Author: Henrique
 */
#ifndef VECTOR2D_H_
#define VECTOR2D_H_

class Vector2D {
public:
    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    ~Vector2D() {}

    float length();
    float normOne();

    float x, y;
};

Vector2D operator+(const Vector2D& left_value, const Vector2D& right_value);
Vector2D operator-(const Vector2D& left_value, const Vector2D& right_value);
Vector2D operator*(const Vector2D& left_value, const float& scalar);

#endif /* VECTOR2D_H_ */
