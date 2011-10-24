#include "Circle.h"
#include <GL/glut.h>
#include <cmath>

#define CIRCLE_PRECISION 16

void Circle::Render() {
    glColor3f(color_.r, color_.g, color_.b);
    float angle = 2 * 3.141592f / (float)(CIRCLE_PRECISION);
    glBegin(GL_POLYGON);
    for(int i = 0; i < CIRCLE_PRECISION; i++) {
    	glVertex2f( radius_ * cos( i * angle ), radius_ * sin( i * angle ) );
    }
    glEnd();
}
