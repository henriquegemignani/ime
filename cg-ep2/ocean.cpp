#include "ocean.h"
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>

// Inicializa objeto oceano com as dimensoes
Ocean::Ocean(int startx, int starty, int endx, int endy) {
	originx = (float) startx;
	originy = (float) starty;
	width = endx - startx;
	height = endy - starty;
}

Ocean::~Ocean() {}

// Desenha o oceano na tela
void Ocean::Render() {
	glPushMatrix();
	glTranslatef (originx, originy, 0.0f);
		glColor3f(0.0f,0.1f,0.8f);
		glBegin(GL_QUADS);
			glVertex3f( 0.0f,   0.0f,  0.0f);
			glVertex3f(width,   0.0f,  0.0f);
			glVertex3f(width, height,  0.0f);
			glVertex3f( 0.0f, height,  0.0f);
		glEnd();
	glPopMatrix();
}
