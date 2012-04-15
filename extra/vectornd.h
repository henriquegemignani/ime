#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <cstdio>
#include <iostream>
#include <cmath>
#include <stdarg.h>

template<int N>
class Vector {
    double val[N];
    
public:
	Vector() { for(int i = 0; i < N; ++i) val[i] = 0; }
    Vector(double a, ...) {
        val[0] = a;
        va_list vl;
        va_start(vl, a);
        for(int i = 1; i < N; ++i) {
            val[i] = va_arg(vl,double);
        }
        va_end(vl);    
    }
    Vector<N> operator=(const Vector<N>& other) {
        if (this != &other) {
            for(int i = 0; i < N; ++i)
                val[i] = other[i];
        }
        return *this;
    }
    
    template<int Y>
    Vector(const Vector<Y>& arg) {
        for(int i = 0; i < N; ++i)
            val[i] = i < Y ? arg[i] : 0;
    }
    
	friend std::istream& operator>> (std::istream& io, Vector<N>& v) {
        for(int i = 0; i < N; ++i)
            io >> v.val[i];
        return io;
    }
	friend std::ostream& operator<< (std::ostream& io, const Vector<N>& v) {
        io << "(";
        for(int i = 0; i < N; ++i) {
            if(i > 0) io << ", ";
            io << v.val[i];
        }
        return io << ")";
    }

	double& operator[](const int i) { return val[i]; }
    
	double operator[](const int i) const { return val[i]; }
    
	double NormSquared() const {
        double result = 0;
        for(int i = 0; i < N; ++i)
            result += val[i] * val[i];
        return result;
    }
    
    double Norm() const { return sqrt(NormSquared()); }
    
    Vector<N> Normalize() const {
        double norm = Norm();
        Vector<N> result;
        for(int i = 0; i < N; ++i)
            result.val[i] = val[i]/norm;
        return result;
    }

	Vector<N> operator+=(const Vector<N>& rhs) {
        for(int i = 0; i < N; ++i)
            val[i] += rhs.val[i];
        return *this;
    }
    
    Vector<N> operator+(const Vector<N>& rhs) const {
        Vector<N> result = rhs;
        result += (*this);
        return result;
    }
    
    Vector<N> operator-() const {
        Vector<N> result;
        for(int i = 0; i < N; ++i)
            result.val[i] = -val[i];
        return result;
    }
    
    Vector<N> operator-=(const Vector<N>& rhs) {
        for(int i = 0; i < N; ++i)
            val[i] -= rhs.val[i];
        return *this;
    }
    
    Vector<N> operator-(const Vector<N>& rhs) const {
        return (-rhs) + (*this);
    }
    
    Vector<N> operator*=(const double& scalar) {
        for(int i = 0; i < N; ++i)
            val[i] *= scalar;
        return *this;
    }
    
    Vector<N> operator*(const double& scalar) const {
        Vector<N> result = *this;
        return result *= scalar;
    }
    
    Vector<N> operator/=(const double& scalar) {
        for(int i = 0; i < N; ++i)
            val[i] /= scalar;
        return *this;
    }
    
    Vector<N> operator/(const double& scalar) const {
        Vector<N> result = *this;
        return result /= scalar;
    }
};

template<int N>
Vector<N> operator*(const double& scalar, const Vector<N>& right_value) {
    return right_value * scalar;
}

Vector<3> VectorProduct(const Vector<3>& a, const Vector<3>& b) {
    Vector<3> result;
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
    return result;
}

#endif
