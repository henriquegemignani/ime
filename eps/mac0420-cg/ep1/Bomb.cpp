/*
 * Bomb.cpp
 *
 *  Created on: 12/04/2011
 *      Author: Henrique
 */

#include "Bomb.h"
#include "base/draw/Circle.h"

Bomb::Bomb(Vector2D &pos) : GameObject(new Circle(0.02f)) {
	this->set_offset(pos);
	z_ = 0;
}

Bomb::~Bomb() {
	// TODO Auto-generated destructor stub
}

void Bomb::Update(float delta_t) {
    if(status_ != ACTIVE) return;
	z_ += delta_t;
	Color c = {0.0f, 0.0f, 0.0f };
	if(z_ < 2) {
		c.r = 0.75f;
		c.g = (4-z_) * 0.2f;
	} else {
		c.r = 0.8f - z_ * 0.15f;
		c.b = 0.9f;
	}
	image_->set_color(c);

	if(z_ > 5.0f)
	    Die();
}
