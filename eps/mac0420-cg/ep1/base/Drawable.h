/*
 * Drawable.h
 *
 *  Created on: 04/04/2011
 *      Author: Henrique
 */
#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "types.h"

class Drawable {
public:
    virtual ~Drawable() {}

    void set_color(Color &color) {
        color_.r = color.r;
        color_.g = color.g;
        color_.b = color.b;
    }

    virtual void Render() {}

protected:
    Drawable() { color_.r = color_.g = color_.b = 1.0f; }
    Color color_;
};

#endif /* DRAWABLE_H_ */
