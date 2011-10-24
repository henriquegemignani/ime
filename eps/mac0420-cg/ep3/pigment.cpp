#include "pigment.h"
#include <cmath>

Vector3D Pigment::GetColorAt(double x, double y, double z) const {
	if(simple) return color1;
	int a = (int)(floor(x/s) + floor(y/s) + floor(z/s));
	return a % 2 ? color2 : color1;
}

