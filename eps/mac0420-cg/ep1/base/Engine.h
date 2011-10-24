/*
 * Engine.h
 *
 *  Created on: 27/03/2011
 *      Author: Henrique
 */
#ifndef ENGINE_H_
#define ENGINE_H_

#include <cstdio>
#define VIDEOMANAGER() Engine::reference()->videomanager()
#define INPUTMANAGER() Engine::reference()->inputmanager()

class VideoManager;
class InputManager;
class Layer;
class Engine {
public:
	static Engine* reference() {
		static Engine *r = NULL;
		return (r == NULL) ? (r = new Engine) : r;
	}
	void Initialize(int *argc, char **argv);

	void Update();
	void Render();

	void Run();


	void TogglePause() { paused_ = !paused_; }
	void FrameStep();

	VideoManager* videomanager() { return video_manager_; }
	InputManager* inputmanager() { return input_manager_; }
	Layer* main_layer() { return main_layer_; }

private:
	Engine() : paused_(false) {}
	virtual ~Engine();

	bool paused_;\
	VideoManager *video_manager_;
	InputManager *input_manager_;
	Layer* main_layer_;
};

#endif /* ENGINE_H_ */
