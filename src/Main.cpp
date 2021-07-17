#include "./Asteroid/Asteroid.h"
#include "./EventHandler/EventHandler.h"
#include "./Laser/Lasers.h"
#include "./Setup/Setup.h" // initial window dimensions and generateSetup()
#include "./Ship/Ship.h"
#include <iostream>
#include <vector> // std::vector

main()
{
	// move this to the asteroids class when it is created.
	srand(time(0));

	sf::RenderWindow window;
	sf::View view;
	generateSetup(window, view);

	Ship ship(window);

	Lasers lasers(window, ship);
	// How do we use a loop or something more sensible here?
	std::vector<Asteroid> asteroids {
		Asteroid(window),
		Asteroid(window),
		Asteroid(window),
		Asteroid(window),
		Asteroid(window)
	};

	// 	sf::Font font;
	// if (!font.loadFromFile("src/fonts/open-sans/OpenSans-Regular.ttf"))
	// {
	// 	sf::Font::Info info = font.getInfo();
	// 	std::cout << "Bugger, font load did not work" << info.family << std::endl;
	// }
	// const float distance = 100.0f;
	// sf::Text tl;
	// tl.setFont(font);
	// tl.setString("-ve -ve");
	// tl.setCharacterSize(24);
	// tl.setFillColor(sf::Color::Red);
	// tl.setPosition(-distance, -distance);

	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Event event;
	EventHandler handler(window, ship);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			handler.process(event);
		}

		window.clear(sf::Color(0, 0, 0));
		window.setView(view);

		// TODO talk to Matt about a for loop on this
		// for (Asteroid asteroid : asteroids)
		for (uint i = 0; i < asteroids.size(); i++)
		{
			asteroids[i].draw();
			ship.hits(asteroids[i]);
		}

		// window.draw(tl);
		lasers.draw();
		ship.draw(deltaTime);
		window.display();
	}
	return 0;
}
