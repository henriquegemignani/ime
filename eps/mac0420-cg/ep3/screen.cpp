#include "screen.h"
#include "matrix.h"

#include <cstdlib>
#include <cmath>
#define PI 3.14159265

Screen::Screen(int w, int h, double fovy) : width(w), height(h) {
	pixels = new Vector3D*[height];
	for(int i = 0; i < height; i++) {
		pixels[i] = new Vector3D[width];
		for(int j = 0; j < width; j++) {
			pixels[i][j] = Vector3D(1, 1, 1);
		}
	}
	plane_height = tan(fovy * PI / 180.0f);
	plane_width = (plane_height * w) / h;
}

Screen::~Screen() {
	for(int i = 0; i < height; i++)
		delete pixels[i];
	delete pixels;
}

void Screen::WriteToFile(FILE *out) {
	fprintf(out,"%s\n%i %i\n%i\n", "P6", width, height, 255);
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++) {
			fputc((unsigned char)(pixels[i][j][0] * 255), out);
			fputc((unsigned char)(pixels[i][j][1] * 255), out);
			fputc((unsigned char)(pixels[i][j][2] * 255), out);
		}
}

void Screen::CalculatePosition(Vector3D eye, Vector3D center, Vector3D up) {
	Vector3D f = (center - eye).Normalize();
	pos = eye + f;
	this->up = up.Normalize();
	right = Vector3D::VectorProduct(f, this->up).Normalize();
	if(DEBUG) std::cout << "Position: " << pos << "\nUp: " << this->up << "\nRight: " <<
			right << "\nHeight: " << plane_height << "\nWidth: " << plane_width << std::endl;
}

Vector3D Screen::GetPixelPosition(int w, int h) {
	double woff = plane_width  * (w - (width - 1) / 2.0f) / (width - 1),
		  hoff = plane_height * (h - (height - 1) / 2.0f) / (height - 1);
	return pos + up * (-hoff) + right * woff;
}

void Screen::SetColor(int w, int h, Vector3D color) {
	pixels[h][w] = color;
}

