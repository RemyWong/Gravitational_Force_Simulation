#include "Platform/Platform.hpp"
#include <cmath>


double euclidian_distance(double x, double y);
double theta(double x, double y);
double grav_accel(double G, double mass, double distance);

int main()
{



	// create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Gravity_Simulation", sf::Style::Titlebar | sf::Style::Close);
	const float fps {60};
	window.setFramerateLimit(fps);
	window.setKeyRepeatEnabled(false);

	/*
	Measurement Units:
	1 pixel = 10^6m
	dt = 10 * 1/60
	*/


	const double dt { 100 / fps }; //s
	const double masses[] {10.f, 20.f, 30.f}; // 10^30 kg
	const double G {6.6743e-11}; // m³kg-1s-²
	const double radius[] {5.f, 10.f, 15.f}; // 10^6 m

	double theta_1 {};
	double G_accel {};
	double distance {};
	double time (dt);
	double distance_travalled {};




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

		time += dt;

		distance = euclidian_distance(coords[1].x - coords[0].x, coords[1].y - coords[0].y);

		theta_1 = theta(coords[1].x - coords[0].x, coords[1].y - coords[0].y);

		G_accel = grav_accel(G, masses[0], distance);

		distance_travalled = euclidian_distance((G_accel * std::pow(time, 2.f) / 2) * std::cos(theta_1), (G_accel * std::pow(time, 2.f) / 2));

		if (distance_travalled > distance){
			coords[0].x = coords[1].x;
			coords[0].y = coords[1].y;
		}
		else{
			coords[0].x = ((G_accel * std::pow(time, 2.f) / 2) * std::cos(theta_1)) + 200.f;
			coords[0].y = ((G_accel * std::pow(time, 2.f) / 2) * std::sin(theta_1)) + 400.f;
		}

		std::cout << G_accel << "\n";
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




		// draw everything here...
		// window.draw(...);

		// end the current frame
		window.display();
	}

	return 0;
}

double euclidian_distance(double x, double y){
	return std::pow(std::pow(x, 2) + std::pow(y, 2), 0.5);
}

double theta(double x, double y){
	return std::atan(y / x);
}

double grav_accel(double G, double mass, double distance){
	return G * mass * std::pow(10, 24) / (std::pow(distance, 2) * std::pow(std::pow(10, 6), 2));
}