#include "Terrain.h"

Terrain::Terrain(sf::Image background, sf::Vector2f position, b2World &world, int colliderSize) {
	Terrain::background = background;
	Terrain::position = position;

	texture.loadFromImage(background);

	sprite.setTexture(texture);
	sprite.setPosition(position);

	Terrain::world = &world;

	Terrain::colliderSize = colliderSize;

	createColliders();
}

void Terrain::createExplosion(sf::Vector2f position, int radius) {
	sf::Vector2f relatviePosition = position - sprite.getPosition();

	for (int x = 0; x < background.getSize().x; x++) {
		for (int y = 0; y < background.getSize().y; y++) {

			float d = sqrt((x - relatviePosition.x) * (x - relatviePosition.x) + (y - relatviePosition.y) * (y - relatviePosition.y));

			if (d < radius) {
				if (x % 8 == 0) {
					physicsPixels.push_back(new PhysicsPixel(position, background.getPixel(x, y), *world));
				}

				// remove pixel
				background.setPixel(x, y, sf::Color::Transparent);
			}
		}
	}

	refreshTerrain();
	createColliders();
}

void Terrain::refreshTerrain() {
	texture.loadFromImage(background);
	sprite.setTexture(texture);
}

void Terrain::createColliders() {
	// erase previous colliders
	for (unsigned i = 0; i < colliderBodies.size(); i++) {
		colliderBodies.at(i)->DestroyFixture(colliderBodies.at(i)->GetFixtureList());
		world->DestroyBody(colliderBodies.at(i));
	}

	colliderBodies.clear();
	rectangles.clear();

	// create colliders
	for (int x = 0; x < background.getSize().x; x++) {
		for (int y = 0; y < background.getSize().y; y++) {
			if (x % colliderSize == 0 && y % colliderSize == 0) {
				if ((int)background.getPixel(x, y).r != 255 && background.getPixel(x, y) != sf::Color::Transparent) {

					if (debugColliders) {
						sf::RectangleShape rec;
						rec.setPosition(x + position.x, y + position.y);
						rec.setSize(sf::Vector2f(colliderSize, colliderSize));
						rec.setFillColor(sf::Color::White);
						rectangles.push_back(rec);
					}

					b2Body* body;

					b2PolygonShape polygonShape;
					b2FixtureDef fixtureDef;
					b2BodyDef bodyDef;

					bodyDef.type = b2_kinematicBody;
					bodyDef.position.Set((x + position.x) * MPP, (y + position.y) * MPP);
					body = world->CreateBody(&bodyDef);

					polygonShape.SetAsBox(colliderSize / 2 * MPP, colliderSize / 2 * MPP);
					fixtureDef.shape = &polygonShape;
					fixtureDef.friction = 1;
					fixtureDef.density = 1;

					body->CreateFixture(&fixtureDef);

					colliderBodies.push_back(body);
				}
			}
		}
	}
}

void Terrain::draw(sf::RenderWindow &window) {
	// draw collider boxes
	if (debugColliders) {
		for (unsigned i = 0; i < rectangles.size(); i++) {
			window.draw(rectangles.at(i));
		}
	}

	// draw physics pixels
	for (unsigned i = 0; i < physicsPixels.size(); i++) {
		physicsPixels.at(i)->draw(window);
	}

	// remove physics pixels if there's over 100
	if (physicsPixels.size() > 100) {
		for (unsigned i = 0; i < physicsPixels.size() - 100; i++) {
			physicsPixels.at(i)->destroy();
			physicsPixels.erase(physicsPixels.begin() + i);
		}
	}

	window.draw(sprite);
}