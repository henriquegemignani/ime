/*
 * VideoManager.cpp
 *
 *  Created on: 27/03/2011
 *      Author: Henrique
 */

#include "VideoManager.h"
#include <GL/glut.h>

VideoManager::VideoManager(int *argc, char **argv) {
	glutInit(argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (400, 400);
}

VideoManager::~VideoManager() {}

void VideoManager::Initialize(std::string& name) {
	glutCreateWindow(name.c_str());

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.15f, 0.15f, 0.75f, 1.0f);
}

void VideoManager::ChangeResolution(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Eixo Y invertido para que o Y da tela seja diretamente relacionado
	// com o Y do jogo
	gluOrtho2D( -1.0f, 1.0f, 1.0f, -1.0f );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	screen_size_.x = w;
	screen_size_.y = h;
}

void VideoManager::Render() {
	glutSwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT);
}
