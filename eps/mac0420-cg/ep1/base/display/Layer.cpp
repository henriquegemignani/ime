/*
 * Layer.cpp
 *
 *  Created on: 31/03/2011
 *      Author: Henrique
 */
#include <algorithm>
#include <GL/glut.h>
#include "Layer.h"

Layer::~Layer() {
    std::vector<Displayable*>::iterator it;
    for(it = childs_.begin(); it != childs_.end(); ++it) {
        delete (*it);
    }
    childs_.clear();
}

void Layer::AddDisplayable(Displayable *obj) {
    childs_.push_back(obj);
}

void Layer::RemoveDisplayable(Displayable *obj) {
    std::vector<Displayable*>::iterator it;
    it = std::find(childs_.begin(), childs_.end(), obj);
    if(it != childs_.end())
        childs_.erase(it);

}

void Layer::Update(float delta_t) {
    std::vector<Displayable*>::iterator it;
    for(it = childs_.begin(); it != childs_.end(); ++it)
        (*it)->Update(delta_t);
}

void Layer::Render() {
	if(!visible_) return;
    std::vector<Displayable*>::iterator it;
    glPushMatrix();
    glTranslatef(offset_.x, offset_.y, 0);
    for(it = childs_.begin(); it != childs_.end(); ++it)
        (*it)->Render();
    glPopMatrix();
}
