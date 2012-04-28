#ifndef MATRIXND_H_
#define MATRIXND_H_

#include <cstdio>
#include <iostream>
#include <cmath>
#include <stdarg.h>
#include "vectornd.h"

template<int N, int M = N>
class Matrix {
    Vector<M> val[N];
public:
	Matrix() {}
    explicit Matrix(Vector<M> a, ...) {
        val[0] = a;
        va_list vl;
        va_start(vl, a);
        for(int i = 1; i < N; ++i) {
            val[i] = va_arg(vl, Vector<M>);
        }
        va_end(vl);    
    }
	~Matrix() {}
    
    Matrix<M, N> Transpose() const {
        Matrix<M, N> result;
        for(int i = 0; i < M; ++i)
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
    
    // TODO: make this MxN?
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
          Vector<M>& operator [](int i)       { return val[i]; }
    const Vector<M>& operator [](int i) const { return val[i]; }
    
	friend std::ostream& operator<< (std::ostream& io, const Matrix<N, M>& ma) {
        Matrix<M, N> m = ma.Transpose();
        for(int i = 0; i < M; ++i) {
            if(i > 0) io << "\n";
            io << m[i];
        }
        return io;
    }
    
    Matrix<N, M> operator+=(const Matrix<N, M>& rhs) {
        for(int i = 0; i < N; ++i)
            val[i] += rhs[i];
        return *this;
    }
    Matrix<N, M> operator+(const Matrix<N, M>& rhs) const {
        Matrix<N, M> result = *this;
        result += rhs;
        return result;
    }
    Matrix<N, M> operator-() const {
        Matrix<N, M> result = *this;
        for(int i = 0; i < N; ++i)
            result[i] = -result[i];
        return result;
    }
    Matrix<N, M> operator-=(const Matrix<N, M>& rhs) {
        for(int i = 0; i < N; ++i)
            val[i] -= rhs[i];
        return *this;
    }
    Matrix<N, M> operator-(const Matrix<N, M>& rhs) const {
        Matrix<N, M> result = *this;
        result -= rhs;
        return result;
    }
    Matrix<N, M> operator*=(const double& scalar) {
        for(int i = 0; i < N; ++i)
            val[i] *= scalar;
        return *this;
    }
    Matrix<N, M> operator*(const double& scalar) const {
        Matrix<N, M> result = *this;
        result *= scalar;
        return *this;
    }
    
    Vector<M> operator*(const Vector<M>& v) const {
        Vector<M> result;
        for(int i = 0; i < N; ++i)
            result += val[i] * v[i];
        return result;
    }
    
    Matrix<N, N> operator*(const Matrix<M, N>& rhs) const {
        Matrix<N, N> result;
        for(int i = 0; i < N; ++i)
            result[i] = (*this) * rhs[i];
    }
};

template<int N, int M>
Matrix<N, M> operator*(const double& scalar, const Matrix<N, M>& r) {
	return r * scalar;
}

#endif /* MATRIXND_H_ */
