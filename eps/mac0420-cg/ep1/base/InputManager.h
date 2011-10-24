/*
 * InputManager.h
 *
 *  Created on: 07/04/2011
 *      Author: henriquelima
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <GL/glut.h>
#include <vector>
#include "Vector2D.h"

#define MOUSE_LEFT GLUT_LEFT_BUTTON
#define MOUSE_RIGHT GLUT_RIGHT_BUTTON


class InputListener {
public:
	InputListener() {}
	~InputListener() {}
	virtual void OnKeyboardInput(unsigned char key) {}
	virtual void OnMousePressed(int button, int x, int y) {}
	virtual void OnMouseUp(int button, int x, int y) {}
};

class InputManager {
public:
	InputManager() { listeners_.clear(); }
	virtual ~InputManager() {}

	void AddInputListener(InputListener* listener);
	void RemoveInputListener(InputListener* listener);

	void SendKeyboardInput(unsigned char key, int x, int y);
	void SendMouseInput(int button, int release, int x, int y);
private:
	std::vector<InputListener*> listeners_;
};

#endif /* INPUTMANAGER_H_ */
