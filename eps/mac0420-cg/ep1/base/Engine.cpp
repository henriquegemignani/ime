/*
 * Engine.cpp
 *
 *  Created on: 27/03/2011
 *      Author: Henrique
 */
#include <GL/glut.h>
#include "Engine.h"
#include "VideoManager.h"
#include "InputManager.h"
#include "display/Layer.h"

#define TIMER_TIME 16

static void reshape(int w, int h) { VIDEOMANAGER()->ChangeResolution(w, h); }
static void display(void) { Engine::reference()->Render(); }
static void idle(int a) {
	Engine::reference()->Update();
	glutTimerFunc(TIMER_TIME, idle, 1);
}
static void keyboard(unsigned char key, int x, int y) {
	Engine::reference()->inputmanager()->SendKeyboardInput(key, x, y);
}
static void mouse(int button, int release, int x, int y) {
	Engine::reference()->inputmanager()->SendMouseInput(button, release, x, y);
}

Engine::~Engine() {
	delete video_manager_;
}

void Engine::Initialize(int *argc, char **argv) {
	video_manager_ = new VideoManager(argc, argv);
	input_manager_ = new InputManager();
	std::string name(argv[0]);
	video_manager_->Initialize(name);

	main_layer_ = new Layer;
	//main_layer_->set_offset(Vector2D(-1, -1));

	glutReshapeFunc (reshape);
	glutDisplayFunc (display);
	glutKeyboardFunc (keyboard);
	glutMouseFunc (mouse);
	glutTimerFunc(TIMER_TIME, idle, 1);
	//glutIdleFunc (idle);
}

void Engine::Update() {
	if(!paused_)
		main_layer_->Update(TIMER_TIME / 1000.0f);
    Render();
}

void Engine::Render() {
    main_layer_->Render();
    video_manager_->Render();
}

void Engine::Run() {
    glutMainLoop();
}

void Engine::FrameStep() {
	paused_ = false;
	Update();
	paused_ = true;
}
