/*
 * Game.cpp
 *
 *  Created on: 11/04/2011
 *      Author: Henrique
 */

#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>
#include <sstream>
#include "base/Engine.h"
#include "base/VideoManager.h"
#include "Game.h"
#include "GameObject.h"
#include "Treco.h"
#include "Bomb.h"

static int points_table[5] = { -4000, -2000, -1000, 1000, 2000 };

Game::Game() {
	Engine::reference()->inputmanager()->AddInputListener(this);
	trecos_.clear();
	bombs_.clear();
	objects_.clear();
	for(int nivel = 0; nivel < 5; nivel++)
		for(int i = 0; i < 4; i++)
			AddTreco(new Treco(nivel));
	queued_bomb_ = false;
	points_ = 0;
}

Game::~Game() {}

bool objectDead (const GameObject* obj) {
    return obj->status() == GameObject::DEAD;
}

void Game::Update(float delta_t) {
	Layer::Update(delta_t);

	std::list<Bomb*>::iterator bomb;
	for(bomb = bombs_.begin(); bomb != bombs_.end(); ++bomb) {
		if((*bomb)->status() != GameObject::ACTIVE) continue;

		std::list<Treco*>::iterator treco;
		for(treco = trecos_.begin(); treco != trecos_.end(); ++treco) {
			if((*treco)->status() != GameObject::ACTIVE) continue;
			Vector2D dist = (*treco)->offset() - (*bomb)->offset();
			if(dist.length() > 0.05f) continue; // constante magica yay

			// Bomb's gonna blow!
			if((*bomb)->z() == (*treco)->z()) {
				(*treco)->Die();
				(*bomb)->Die();
				points_ += points_table[(*treco)->z()];
			}
		}
	}

	if(queued_bomb_) {
	    AddBomb(new Bomb(queued_bomb_position_));
		queued_bomb_ = false;
	}

	std::list<GameObject*>::iterator it;
	for(it = objects_.begin(); it != objects_.end(); ++it)
	    if((*it)->status() == GameObject::DEAD)
	        RemoveDisplayable(*it);
	trecos_.remove_if(objectDead);
	bombs_.remove_if(objectDead);
	objects_.remove_if(objectDead);
}

void Game::AddTreco(Treco * treco) {
    if(treco != NULL) {
        trecos_.push_front(treco);
        objects_.push_front(treco);
        AddDisplayable(treco);
    }
}
void Game::AddBomb(Bomb * bomb) {
    if(bomb != NULL) {
        bombs_.push_front(bomb);
        objects_.push_front(bomb);
        AddDisplayable(bomb);
    }
}

void Game::Render() {
    Layer::Render();
    glRasterPos2f(-0.9f, -0.9f);
    glColor3f( 0.0f, 0.0f, 0.0f );
    std::stringstream ss;
    ss << points_;
    const char *c = ss.str().c_str();
    for (; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}
void Game::OnKeyboardInput(unsigned char key) {
	switch(key) {
	case 27: // ESCAPE
	case 'q':
		exit(0);
	case 'p':
		Engine::reference()->TogglePause();
		break;
	default:
		break;
	}
}

void Game::OnMousePressed(int button, int x, int y) {
	if(button == MOUSE_LEFT) {
		queued_bomb_ = true;
		Vector2D screen_size = VIDEOMANAGER()->screen_size();
		queued_bomb_position_ = Vector2D(x/screen_size.x, y/screen_size.y) * 2.0f - Vector2D(1.0f, 1.0f);
	} else if(button == MOUSE_RIGHT) {
		Engine::reference()->FrameStep();
	}
}

