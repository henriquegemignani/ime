/*
 * VideoManager.h
 *
 *  Created on: 27/03/2011
 *      Author: Henrique
 */
#ifndef VIDEOMANAGER_H_
#define VIDEOMANAGER_H_

#include <cstdio>
#include <string>

#include "Vector2D.h"

class Engine;
class VideoManager {
friend class Engine;
public:
	void Initialize(std::string& name);
	void ChangeResolution(int w, int h);
	void Render();

	Vector2D screen_size() { return screen_size_; }

private:
	Vector2D screen_size_;
	VideoManager(int *argc, char **argv);
	virtual ~VideoManager();
};

#endif /* VIDEOMANAGER_H_ */
