/*
 * Game.h
 *
 *  Created on: 11/04/2011
 *      Author: Henrique
 */

#ifndef GAME_H_
#define GAME_H_

#include <list>
#include "base/InputManager.h"
#include "base/Vector2D.h"
#include "base/display/Layer.h"

class Treco;
class Bomb;
class GameObject;
class Game: public Layer, public InputListener {
public:
	Game();
	~Game();
	void Update(float delta_t);

	void AddTreco(Treco * treco);
	void AddBomb(Bomb * bomb);

	void Render();
	void OnKeyboardInput(unsigned char key);
	void OnMousePressed(int button, int x, int y);
private:
	std::list<Treco*> trecos_;
	std::list<Bomb*> bombs_;
	std::list<GameObject*> objects_;
	bool queued_bomb_;
	Vector2D queued_bomb_position_;
	int points_;
};

#endif /* GAME_H_ */
