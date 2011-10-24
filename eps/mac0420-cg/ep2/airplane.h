#ifndef AIRPLANE_H_
#define AIRPLANE_H_

#include "vector3d.h"

class Airplane {
public:
	Airplane(Vector3D pos, Vector3D rot, float vel);
	~Airplane();
	
	void Camera(int viewmode);
	void Render();
	void Update();
	void UpdateRot(Vector3D add);
	void UpdateRotVelocity(Vector3D add);
	void StopRotVelocity();
	void UpdateVelocity(float vel);
	
	void Dump();

private:
	Vector3D position, rotation, rotvel;
	float velocity;
};

#endif
