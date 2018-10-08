#include "PhysicsPixel.h"

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

PhysicsPixel::PhysicsPixel(sf::Vector2f center, sf::Color color, b2World &world) {
	PhysicsPixel::world = &world;

	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;
	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(center.x * MPP, center.y * MPP);
	body = PhysicsPixel::world->CreateBody(&bodyDef);

	polygonShape.SetAsBox(5 / 2 * MPP, 5 / 2 * MPP);
	fixtureDef.shape = &polygonShape;
	fixtureDef.friction = 1;
	fixtureDef.density = 0.7f;

	body->CreateFixture(&fixtureDef);

	// Create shape SFML
	shape.setSize(sf::Vector2f(5, 5));
	shape.setOrigin(5 / 2, 5 / 2);
	shape.setFillColor(color);

	body->ApplyForce(b2Vec2(RandomFloat(-1, 1), RandomFloat(-1, -1)), body->GetWorldCenter(), true);
}

void PhysicsPixel::draw(sf::RenderWindow &window) {
	if (body != NULL) {
		float angle = body->GetAngle();
		b2Vec2 position = body->GetPosition();
		shape.setPosition(position.x * PPM, position.y * PPM);
		shape.setRotation((angle * 180) / 3.14159265358979323846264338327950288f);

		window.draw(shape);
	}
}

void PhysicsPixel::destroy() {
	body->DestroyFixture(body->GetFixtureList());
	world->DestroyBody(body);
}