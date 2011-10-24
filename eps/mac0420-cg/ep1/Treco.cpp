/*
 * Treco.cpp
 *
 *  Created on: 07/04/2011
 *      Author: henriquelima
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "Treco.h"
#include "base/draw/Rect.h"
#include "base/Vector2D.h"

float randf(float max = 1.0f) {
	return (rand() * max) / RAND_MAX;
}

Treco::Treco(int z) : GameObject(NULL) {
	this->set_image(rect_ = new Rect(Vector2D(0.1f, 0.1f)));
	z_ = (float)(z);
	Color c = {0.0f, 0.0f, 0.0f };
	if(z_ < 2) {
		c.r = 0.75f;
		c.g = (4-z_) * 0.2f;
	} else {
		c.r = 0.8f - z_ * 0.15f;
		c.b = 0.9f;
	}
	rect_->set_color(c);
	set_offset(Vector2D(1 - randf(2.0f), 1 - randf(2.0f)));
	movement_ = Vector2D(0.5f - randf(1.0f), 0.5f - randf(1.0f));
	flashing_ = 1.0f;
}

void Treco::Update(float delta_t) {
	if(status_ == ACTIVE) {
		Vector2D newpos = offset_ + movement_ * delta_t;
		Vector2D left  = newpos - rect_->size() * 0.5f;
		Vector2D right = newpos + rect_->size() * 0.5f;
		if(right.x > 1.0f || left.x < -1.0f)
			movement_.x *= -1.0f;
		if(right.y > 1.0f || left.y < -1.0f)
			movement_.y *= -1.0f;
		if(right.x >  1.0f) newpos.x =  1.0f - rect_->size().x * 0.5f;
		if(left.x  < -1.0f) newpos.x = -1.0f + rect_->size().x * 0.5f;
		if(right.y >  1.0f) newpos.y =  1.0f - rect_->size().y * 0.5f;
		if(left.y  < -1.0f) newpos.y = -1.0f + rect_->size().x * 0.5f;
		this->set_offset(newpos);
	} else {
		Color c = { 1.0f, 0.1f, 0.1f };
		flashing_ -= 2 * delta_t;
		if(flashing_ < 0.3f) flashing_ += 0.7f;
		c.r = flashing_;
		rect_->set_color(c);

		blowing_up_ += delta_t;
		if(blowing_up_ > 1) status_ = DEAD;
	}
}

void Treco::Die() {
	status_ = DYING;
	blowing_up_ = 0.0f;
}
