/*
 * GameObject.cpp
 *
 *  Created on: 12/04/2011
 *      Author: Henrique
 */

#include "GameObject.h"

GameObject::GameObject(Drawable *image) : Sprite(image) {
	status_ = ACTIVE;
}

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
}
