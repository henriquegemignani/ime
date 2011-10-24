#ifndef SCREEN_H_
#define SCREEN_H_

#include "vector3d.h"
#include <cstdio>

class Screen {
public:
	Screen(int w, int h, double fovy);
	~Screen();

	void WriteToFile(FILE *out);
	void CalculatePosition(Vector3D eye, Vector3D center, Vector3D up);
	Vector3D GetPixelPosition(int w, int h);
	void SetColor(int w, int h, Vector3D color);

private:
	int width, height;
	double plane_height, plane_width;
	Vector3D **pixels, pos, up, right;

};

#endif /* SCREEN_H_ */
