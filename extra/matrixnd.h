#ifndef MATRIXND_H_
#define MATRIXND_H_

#include <cstdio>
#include <iostream>
#include <cmath>
#include <stdarg.h>
#include "vectornd.h"

/* Always NxN! */

template<int N>
class Matrix {
    Vector<N> val[N];
public:
	Matrix() {}
    Matrix(Vector<N> a, ...) {
        val[0] = a;
        va_list vl;
        va_start(vl, a);
        for(int i = 1; i < N; ++i) {
            val[i] = va_arg(vl, Vector<N>);
        }
        va_end(vl);    
    }
	~Matrix() {}
    
    Matrix<N> Transpose() const {
        Matrix<N> result;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                result[i][j] = val[j][i];
        return result;
    }
    
	Matrix<N> Inverse() const {
        Matrix<N> a;
        Matrix<N> q, r;
        if(!QR(q, r)) {
            // Matrix não tem inversa.
            return a;
        }
        Matrix<N> qt = q.Transpose();
        for(int i = N - 1; i >= 0; --i) {
            for(int j = 0; j < N; j++) {
                double x = qt[j][i];
                for(int k = i + 1; k < N; ++k) {
                    x -= r[k][i] * a[j][k];
                }
                a[j][i] = x / r[i][i];
            }
        }
        return a;
    }
    
	bool QR(Matrix<N> &q, Matrix<N> &r) const {
        // Cria uma cópia da matrix atual
        Matrix<N> v = *this;

        // Gram-Schmidt Modificado
        for(int i = 0; i < N; ++i) {
            r[i][i] = v[i].Norm();
            if(r[i][i] < 1.0e-6) // Matrix não tem posto completo
                return false;
            q[i] = v[i] / r[i][i];
            for(int j = i + 1; j < N; ++j) {
                r[j][i] = (q[i]) * (v[j]);
                v[j] = v[j] - r[j][i] * q[i];
            }
        }
        return true;
    }

	double operator() (int i, int j)    const { return val[i][j]; }
          Vector<N>& operator [](int i)       { return val[i]; }
    const Vector<N>& operator [](int i) const { return val[i]; }
    
	friend std::ostream& operator<< (std::ostream& io, const Matrix<N>& ma) {
        Matrix<N> m = ma.Transpose();
        for(int i = 0; i < N; ++i) {
            if(i > 0) io << "\n";
            io << m[i];
        }
        return io;
    }
    
    Matrix<N> operator+=(const Matrix<N>& rhs) {
        for(int i = 0; i < N; ++i)
            val[i] += rhs[i];
        return *this;
    }
    Matrix<N> operator+(const Matrix<N>& rhs) const {
        Matrix<N> result = *this;
        result += rhs;
        return result;
    }
    Matrix<N> operator-() const {
        Matrix<N> result = *this;
        for(int i = 0; i < N; ++i)
            result[i] = -result[i];
        return result;
    }
    Matrix<N> operator-=(const Matrix<N>& rhs) {
        for(int i = 0; i < N; ++i)
            val[i] -= rhs[i];
        return *this;
    }
    Matrix<N> operator-(const Matrix<N>& rhs) const {
        Matrix<N> result = *this;
        result -= rhs;
        return result;
    }
    Matrix<N> operator*=(const double& scalar) {
        for(int i = 0; i < N; ++i)
            val[i] *= scalar;
        return *this;
    }
    Matrix<N> operator*(const double& scalar) const {
        Matrix<N> result = *this;
        result *= scalar;
        return *this;
    }
    
    Vector<N> operator*(const Vector<N>& v) const {
        Vector<N> result;
        for(int i = 0; i < N; ++i)
            result += val[i] * v[i];
        return result;
    }
    
    Matrix<N> operator*(const Matrix<N>& rhs) const {
        Matrix<N> result;
        for(int i = 0; i < N; ++i)
            result[i] = (*this) * rhs[i];
    }
};

template<int N>
Matrix<N> operator*(const double& scalar, const Matrix<N>& r) {
	return r * scalar;
}

#endif /* MATRIXND_H_ */
