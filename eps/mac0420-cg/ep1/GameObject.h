/*
 * GameObject.h
 *
 *  Created on: 12/04/2011
 *      Author: Henrique
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "base/display/Sprite.h"

class GameObject: public Sprite {
public:
	enum Status {
		ACTIVE,
		DYING,
		DEAD
	};
	int z() const { return static_cast<int>(z_); }
	Status status() const { return status_; }

	~GameObject();
	virtual void Die() { status_ = DEAD; }
protected:
	GameObject(Drawable *image = NULL);
	float z_;
	Status status_;
};

#endif /* GAMEOBJECT_H_ */
