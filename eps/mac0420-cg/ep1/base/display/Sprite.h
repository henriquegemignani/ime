#ifndef SPRITE_H_
#define SPRITE_H_

#include "../Displayable.h"
#include <cstdio>

class Drawable;

class Sprite: public Displayable {
public:
    Sprite(Drawable *image = NULL) : image_(image) {}
    virtual ~Sprite();

    void set_image(Drawable *image) { image_ = image; }

    virtual void Update(float delta_t) {}
    void Render();

protected:
    Drawable *image_;
};

#endif /* SPRITE_H_ */
