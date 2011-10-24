#include "Rect.h"
#include <GL/glut.h>

void Rect::Render() {
    glColor3f(0.5f, 0.5f, 0.5f);
    glRectf( -size_.x * 0.6f, -size_.y * 0.6f, size_.x * 0.6f, size_.y * 0.6f );
    glColor3f(color_.r, color_.g, color_.b);
    glRectf( -size_.x * 0.5f, -size_.y * 0.5f, size_.x * 0.5f, size_.y * 0.5f );
}
