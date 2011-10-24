#include "matrix.h"

#define n 3

Matrix::Matrix() {
	for(int i = 0; i < n; i++)
		val[i] = Vector3D();
}

Matrix::Matrix(Vector3D a, Vector3D b, Vector3D c) {
	val[0] = a;
	val[1] = b;
	val[2] = c;
}

Matrix Matrix::Transpose() {
	return Matrix(Vector3D(val[0][0], val[1][0], val[2][0]),
				  Vector3D(val[0][1], val[1][1], val[2][1]),
				  Vector3D(val[0][2], val[1][2], val[2][2]));
}
Matrix Matrix::Inverse() {
	Matrix a;
	Matrix q, r;
	if(!QR(q, r)) {
		// Matrix não tem inversa.
		return a;
	}
	Matrix qt = q.Transpose();
	for(int i = n - 1; i >= 0; --i) {
		for(int j = 0; j < n; j++) {
			double x = qt[j][i];
			for(int k = i + 1; k < n; ++k) {
				x -= r[k][i] * a[j][k];
			}
			a[j][i] = x / r[i][i];
		}
	}
	return a;
}
bool Matrix::QR(Matrix &q, Matrix &r) {
	// Cria uma cópia da matrix atual
	Matrix v;
	for(int i = 0; i < n; ++i)
		v[i] = val[i];

	// Gram-Schmidt Modificado
	for(int i = 0; i < n; ++i) {
		r[i][i] = v[i].Norm();
		if(r[i][i] < 1.0e-6) // Matrix não tem posto completo
			return false;
		q[i] = v[i] / r[i][i];
		for(int j = i + 1; j < n; ++j) {
			r[j][i] = (q[i]) * (v[j]);
			v[j] = v[j] - r[j][i] * q[i];
		}
	}
	return true;
}


double Matrix::operator ()(int i, int j) const { return val[i][j]; }

Vector3D& Matrix::operator [](int i) { return val[i]; }
Vector3D Matrix::operator [](int i) const { return val[i]; }

Matrix operator+(const Matrix& l, const Matrix& r) {
	return Matrix(l[0] + r[0], l[1] + r[1], l[2] + r[2]);
}

Matrix operator-(const Matrix& l, const Matrix& r) {
	return Matrix(l[0] - r[0], l[1] - r[1], l[2] - r[2]);
}

Matrix operator*(const Matrix& l, const Matrix& r) {
	return Matrix(l * r[0], l * r[1], l * r[2]);
}

Matrix operator*(const Matrix& l, const double& scalar) {
	return Matrix(l[0] * scalar, l[1] * scalar, l[2] * scalar);
}

Matrix operator*(const double& scalar, const Matrix& r) {
	return r * scalar;
}

Vector3D operator*(const Matrix& l, const Vector3D& v) {
	return (l[0] * v[0] + l[1] * v[1] + l[2] * v[2]);
}

std::ostream& operator<< (std::ostream& io, Matrix& ma) {
	Matrix m = ma.Transpose();
	return io << m[0] << "\n" << m[1] << "\n" << m[2];
}
