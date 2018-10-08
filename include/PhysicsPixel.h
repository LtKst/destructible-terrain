//header guard at start of header file
#ifndef PHYSICS_PIXEL
#define PHYSICS_PIXEL

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class PhysicsPixel {
	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(5, 5));

	b2World* world;
	b2Body* body;

	float PPM = 64.f;
	float MPP = 0.015625f;

public:
	PhysicsPixel(sf::Vector2f, sf::Color, b2World &world);
	void draw(sf::RenderWindow &window);
	void destroy();
};

#endif