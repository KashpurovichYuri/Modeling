#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "lattice.hpp"

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Crystal lattice");

	sf::Vector2f min_point(0.0f, 0.0f);
	sf::Vector2f max_point(775.0f, 575.0f);

	auto length = 50.0f;
	auto rad = 2.0f;
	auto mass = 1e-5f;
	auto stifness = 5e-3f;
	Latice lattice(window.getSize().x, window.getSize().y, length, rad, mass, stifness);

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
		
		window.clear();

		for (auto i = 0U; i < lattice.getParticlesSize(); ++i)
		{
			sf::CircleShape circle(2 * lattice.getParticlesRad());

			auto pos1 = lattice.getIndexedParticle(i)->position();
			auto pos2 = sf::Vector2f(lattice.getParticlesRad(), lattice.getParticlesRad());
			sf::Vector2f pos(pos1 + pos2);

			circle.setPosition(pos);

			circle.setFillColor(sf::Color::Red);

			window.draw(circle);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}