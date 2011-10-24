#include <GL/glut.h>
#include "Sprite.h"
#include "../Drawable.h"

Sprite::~Sprite() {
    if(image_ != NULL)
        delete image_;
}

void Sprite::Render() {
    if(image_ != NULL && visible_) {
        glPushMatrix();
        glTranslatef(offset_.x, offset_.y, 0);
        image_->Render();
        glPopMatrix();
    }
}
