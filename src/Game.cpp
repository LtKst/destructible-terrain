#include "Game.h"

#define TIMESTEP 1.0f/60.0f     // Refresh time
#define VELITER 10              // Number of iterations per tick to calculate speed
#define POSITER 10              // Number tick iterations to calculate the position

#define WIDTH 800
#define HEIGHT 600

void Game::run() {
	// define the world
	b2World world = b2World(b2Vec2(0.f, 6.f));

	// define the window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Destructible terrain", sf::Style::Close);
	window.setFramerateLimit(60);

	// terrain
	sf::Image image;
	image.loadFromFile("Background.png");

	Terrain terrain = Terrain(image, sf::Vector2f(0, HEIGHT /  2), world, 16);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clicking for explosions
		if (leftMouseButton.getButtonDown())
		{
			int x = sf::Mouse::getPosition(window).x;
			int y = sf::Mouse::getPosition(window).y;

			terrain.createExplosion(sf::Vector2f(x, y), 10);
		}

		// drawing stuff
		window.clear(sf::Color(135, 170, 230));

		// update world Box2D
		world.Step(TIMESTEP, VELITER, POSITER);

		terrain.draw(window);

		window.display();
	}
}