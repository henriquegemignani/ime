#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <GL/glut.h>

#include "base/Engine.h"
#include "base/display/Layer.h"
#include "Game.h"

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
    srand(time(NULL));
    Engine *engine = Engine::reference();
    engine->Initialize(&argc, argv);
    engine->main_layer()->AddDisplayable(new Game);
	engine->Run();
	return 0;
}

