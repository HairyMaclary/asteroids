#pragma once

#include "./Asteroid/Asteroid.h"

class Ship
{
private:
	sf::RenderWindow& window;
	const float height { 20.f };
	sf::Vector2f position { 0.0f, 0.0f };
	sf::Vector2f velocity;
	const float velocityDrag { 0.98f };
	const float maxTime { 1.0f / 60.0f }; // 60fps
	const float turnRate { 0.15f };
	const float inertia { 0.6f };
	float runningTime { 0 };
	bool boosting { false };
	sf::ConvexShape ship;
	float heading { 0 };
	bool alive { true };

	void update(float deltaTime);
	void setPoints();
	void checkKeys();
	void edges();

public:
	Ship(sf::RenderWindow& mainWindow);
	void draw(float deltaTime);
	void turn(float angle);
	void boost();
	void reset();
	void hits(Asteroid& asteroid);
};