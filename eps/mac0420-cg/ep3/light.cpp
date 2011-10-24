#include "light.h"

Vector3D Light::GetColorAt(Vector3D location) {
	double d = (location - pos).Norm();
	return rgb / (atenuation[0] + atenuation[1] * d + atenuation[2] * d * d);
}
