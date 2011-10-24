/*
 * Treco.h
 *
 *  Created on: 07/04/2011
 *      Author: henriquelima
 */

#ifndef TRECO_H_
#define TRECO_H_

#include "GameObject.h"
#include "base/Vector2D.h"

class Rect;
class Treco: public GameObject {
public:
	Treco(int z);
	virtual ~Treco() {}

	void Update(float delta_t);
	void Die();
private:
	Rect *rect_;
	Vector2D movement_;
	float flashing_, blowing_up_;
};

#endif /* TRECO_H_ */
