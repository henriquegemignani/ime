#ifndef MATRIX_H_
#define MATRIX_H_

/* Sempre 3x3! */
#include "vector3d.h"

class Matrix {
public:
	Matrix();
	Matrix(Vector3D a, Vector3D b, Vector3D c);
	~Matrix() {}
	Matrix Transpose();
	Matrix Inverse();
	bool QR(Matrix &Q, Matrix &R);

	double operator() (int i, int j) const;
	Vector3D& operator[] (int i);
	Vector3D operator[] (int i) const;
	friend std::ostream& operator<< (std::ostream& i, Matrix& m);

private:
	Vector3D val[3];
};

Matrix operator+(const Matrix& left_value, const Matrix& right_value);
Matrix operator-(const Matrix& left_value, const Matrix& right_value);
Matrix operator*(const Matrix& left_value, const Matrix& right_value);
Matrix operator*(const Matrix& left_value, const double& scalar);
Matrix operator*(const double& scalar, const Matrix& right_value);
Vector3D operator*(const Matrix& left_value, const Vector3D& vector);

#endif /* MATRIX_H_ */
