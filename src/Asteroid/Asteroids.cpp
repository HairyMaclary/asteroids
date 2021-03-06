#include "./Asteroids.h"
#include "../src/Asteroid/Asteroid.h"
#include "../src/Laser/Lasers.h"
#include "../src/Ship/Ship.h"

Asteroids::Asteroids(sf::RenderWindow& renderwindow, Ship& ship, Lasers& lasers, Score& score) :
	window { renderwindow },
	ship { ship },
	lasers { lasers },
	score { score }
{
	srand(time(0));

	for (uint i = 0; i < initialAsteroidCount; ++i)
	{
		asteroids.push_back(new Asteroid(window, ship.position));
	}
}

// Separate state and presentation.
// Keep as much logic in the update() as possible. That is, do all the logic required to update
// state before the GPU does it's work. The GPU is not good at branching and other operations.
void Asteroids::update(float deltaTime)
{
	std::list<Asteroid*>::iterator it;
	for (it = asteroids.begin(); it != asteroids.end();)
	{
		const bool hit = lasers.hits(**it);
		if (hit)
		{
			auto radius = (*it)->getRadius();
			auto pos = (*it)->getPosition();

			delete (*it);
			(*it) = nullptr;
			it = asteroids.erase(it);

			score.update(radius);

			if (radius > 5)
			{
				asteroids.emplace_back(new Asteroid(window, pos, radius / 2));
				asteroids.emplace_back(new Asteroid(window, pos, radius / 2));
			}
		}
		else
		{
			++it;
		}
	}

	runningTime += deltaTime;
	if (ship.alive && runningTime > spawnTime)
	{
		runningTime = 0;
		spawnTime *= 0.95f;
		// prevent late game 'avalanche' of asteroids
		if (spawnTime < 3)
		{
			spawnTime = 10.0f;
		}
		asteroids.emplace_back(new Asteroid(window, ship.position));
	}
}

void Asteroids::draw(float deltaTime)
{
	update(deltaTime);

	std::list<Asteroid*>::iterator it;
	for (it = asteroids.begin(); it != asteroids.end(); ++it)
	{
		(**it).draw();
		ship.hits(**it);
	}
}
