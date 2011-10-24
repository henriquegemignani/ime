/*
 * Bomb.h
 *
 *  Created on: 12/04/2011
 *      Author: Henrique
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "GameObject.h"
#include "base/Vector2D.h"

class Bomb: public GameObject {
public:
	Bomb(Vector2D &pos);
	virtual ~Bomb();

	void Update(float delta_t);
};

#endif /* BOMB_H_ */
