#ifndef COMMON_H_
#define COMMON_H_

#include <vector>
#include "light.h"
#include "object.h"

typedef struct {
	std::vector<Light*> lights;
	std::vector<Object*> objects;
	Light* ambient_light;
} Environment;

#endif /* COMMON_H_ */
