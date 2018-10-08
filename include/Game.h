#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "MouseButton.h"
#include "Terrain.h"
#include "PhysicsPixel.h"

class Game {
	MouseButton leftMouseButton = MouseButton(sf::Mouse::Left);

	public:
		void run();
};

#endif