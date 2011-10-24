#include "island.h"
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>

// Inicializa um objeto ilha com dimensoes e matriz de alturas
Island::Island(int startx, int starty, int endx, int endy, char *filename) {
	originx = (float) startx;
	originy = (float) starty;
	width = endx - startx;
	height = endy - starty;
	FILE *terrain = fopen(filename, "r");
	height_map = new int*[width];
	for(int i = 0; i < width; i++)
		height_map[i] = new int[height];
		
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			fscanf(terrain, "%d", &height_map[j][i]);
	fclose(terrain);
}

Island::~Island() {
	for(int i = 0; i < width; i++)
		delete height_map[i];
	delete height_map;
}

// Desenha a ilha com cores de acordo com as alturas
void Island::Render() {
	glPushMatrix();
	glTranslatef (originx, originy, 0.0f);
	for(int i = 0; i < width - 1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j < height; j++) {
            if (height_map[i][j] <= 9 || height_map[i][j] >= 40) 
                glColor3f(0.0f, 0.0f, 0.0f); //preto
            else if (height_map[i][j] >= 17 && height_map[i][j] < 40) 
                glColor3f(0.13f, 0.26f, 0.12f); //verde escuro
            else 
                glColor3f(0.60f, 0.40f, 0.08f); 
		    glVertex3f(i, j,  height_map[i][j]);

            if (height_map[i+1][j] <= 9 || height_map[i+1][j] >= 40) 
                glColor3f(0.10f, 0.10f, 0.10f); //cinza
            else if (height_map[i+1][j] >= 17 && height_map[i+1][j] < 40) 
                glColor3f(0.20f, 0.80f, 0.20f); //verde claro
            else 
                glColor3f(0.76f, 0.60f, 0.42f); 
            glVertex3f(i+1, j,  height_map[i+1][j]);
        }
		glEnd();
	}
	glPopMatrix();
}
