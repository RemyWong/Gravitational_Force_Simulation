#include "Platform/Platform.hpp"

int main()
{

	// create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Gravity_Simulation", sf::Style::Titlebar | sf::Style::Close);
	const float fps {60};
	window.setFramerateLimit(fps);
	window.setKeyRepeatEnabled(false);

	//const float dt { 1 / 60}; //s
	//const float masses[] {10.f, 20.f, 30.f}; // 10^6 kg
	//const float G {6.6743e-11}; // m³kg-1s-²
	const float radius[] {5.f, 10.f, 15.f}; // 10^6 m

	sf::Vector2f coords[] {
		sf::Vector2f(200.f, 400.f),
		sf::Vector2f(400.f, 600.f),
		sf::Vector2f(900.f, 500.f)
	};


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



		// clear the window with black color
		window.clear(sf::Color::Black);

		sf::CircleShape planets[] {
			sf::CircleShape(radius[0]),
			sf::CircleShape(radius[1]),
			sf::CircleShape(radius[2])
		};

		int *radius_iterator {new int{0}};
		for (auto planet : planets){
			planet.setOrigin(radius[*radius_iterator], radius[*radius_iterator]);
			planet.setPosition(coords[*radius_iterator]);
			window.draw(planet);
			*radius_iterator = *radius_iterator + 1;
		}

		delete radius_iterator;
		radius_iterator = nullptr;




		// draw everything here...
		// window.draw(...);

		// end the current frame
		window.display();
	}

	return 0;
}
