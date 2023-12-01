#include <iostream>
#include "Game.h"

int main() {
	//Init srand
	srand(static_cast<unsigned>(time(NULL)));

	//Init Game Engine
	Game game;
	while (game.getWindowIsOpen()) {
		//Update
		game.update();
		//Render
		game.render();
	}

	//End of application
	return 0;
}