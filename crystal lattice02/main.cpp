#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "lattice.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800U, 600U), "Crystal lattice");

	sf::Vector2f min_point(  0.0f,   0.0f);
	sf::Vector2f max_point(775.0f, 575.0f);

	const auto N_x = 10U;
	const auto N_y = 10U;

	const auto a = 50.0f;

	const auto r = 2.5f;

	const auto mass = 0.1f;

	const auto g = sf::Vector2f (0.0f, 10.0f);

	const auto stiffness = 0.5f;

	Lattice lattice(min_point, max_point, N_x, N_y, a, r, mass, stiffness, g);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		lattice.update();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			lattice.push(sf::Vector2f(0.0f, -1.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			lattice.push(sf::Vector2f(0.0f, 1.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			lattice.push(sf::Vector2f(-1.0f, 0.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			lattice.push(sf::Vector2f(1.0f, 0.0f));
		}

		window.clear();
		
		for (auto i = 0U; i < lattice.particles().size(); ++i)
		{
			sf::CircleShape circle(2.0f * r);

			circle.setPosition(lattice.particle(i)->position() + sf::Vector2f(r, r));

			circle.setFillColor(sf::Color::Red);

			window.draw(circle);
		}
	
		window.display();
	}
	
	// system("pause");

	return EXIT_SUCCESS;
}
