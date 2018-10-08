#ifndef TERRAIN
#define TERRAIN

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "PhysicsPixel.h"

class Terrain {
	void refreshTerrain();
	void createColliders();

	sf::Image background;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;

	b2World* world;
	std::vector<b2Body*> colliderBodies;
	std::vector<sf::RectangleShape> rectangles;
	int colliderSize;

	float PPM = 64.f;
	float MPP = 0.015625f;

	bool debugColliders = false;

	std::vector<PhysicsPixel* > physicsPixels;
public:
	Terrain(sf::Image, sf::Vector2f, b2World &world, int colliderSize);

	void createExplosion(sf::Vector2f, int);
	void draw(sf::RenderWindow &window);
};

#endif