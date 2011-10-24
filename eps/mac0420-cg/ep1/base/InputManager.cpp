/*
 * InputManager.cpp
 *
 *  Created on: 07/04/2011
 *      Author: henriquelima
 */

#include <algorithm>
#include "InputManager.h"

void InputManager::AddInputListener(InputListener* listener) {
	listeners_.push_back(listener);
}
void InputManager::RemoveInputListener(InputListener* listener) {
	std::vector<InputListener*>::iterator it;
	it = std::find(listeners_.begin(), listeners_.end(), listener);
	if(it != listeners_.end())
		listeners_.erase(it);
}

void InputManager::SendKeyboardInput(unsigned char key, int x, int y) {
	std::vector<InputListener*>::iterator it;
	for(it = listeners_.begin(); it != listeners_.end(); ++it)
		(*it)->OnKeyboardInput(key);
}

void InputManager::SendMouseInput(int button, int release, int x, int y) {
	std::vector<InputListener*>::iterator it;
	for(it = listeners_.begin(); it != listeners_.end(); ++it)
		if(release == 0)
			(*it)->OnMousePressed(button, x, y);
		else
			(*it)->OnMouseUp(button, x, y);
}
