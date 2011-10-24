/*
 * Displayable.h
 *
 *  Created on: 31/03/2011
 *      Author: Henrique
 */
#ifndef DISPLAYABLE_H_
#define DISPLAYABLE_H_

#include "Vector2D.h"

class Displayable {
public:
    virtual ~Displayable() {}

    virtual void Update(float delta_t) {}
    virtual void Render() {}

    void set_offset(Vector2D offset) { offset_ = offset; }
    Vector2D offset() { return offset_; }
    void set_visible(bool visible) { visible_ = visible; }
    bool visible() { return visible_; }

protected:
    Displayable() : visible_(true) {}
    bool visible_;
    Vector2D offset_;
};

#endif /* DISPLAYABLE_H_ */
