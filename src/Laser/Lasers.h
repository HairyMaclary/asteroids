#pragma once
#include "../src/Ship/Ship.h"
#include "./Asteroid/Asteroid.h"
#include "./Laser.h"
#include <vector>

class Lasers
{
private:
	sf::RenderWindow& window;
	Ship& ship;
	std::vector<Laser*> bolts;
	float maxTime { 1.0f / 5.0f };
	float runningTime { maxTime };
	sf::SoundBuffer destructionSoundBuffer;
	sf::Sound destructionSound;
	sf::SoundBuffer boltSoundBuffer;
	sf::Sound boltSound;

	void checkKeys();
	void deleteOldBolts();

public:
	Lasers(sf::RenderWindow& window, Ship& craft);
	void draw(float deltaTime);
	bool hits(Asteroid& asteroid);
};