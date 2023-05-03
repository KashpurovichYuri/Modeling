#include <vector>
#include <chrono>
#include <random>

#include <SFML/Graphics.hpp>

#include <boost/multi_array.hpp>

enum class Direction
{
	down,
	left,
	right,
	up
};

struct Particle
{
	Particle(unsigned int x, unsigned int y) :
		m_x(x), m_y(y)
	{}

	~Particle() noexcept = default;

	unsigned int m_x;
	unsigned int m_y;
};

void check_boundaries(std::shared_ptr < Particle >& particle, unsigned int width, unsigned int height)
{
	if (particle->m_x <= -1)
		particle->m_x = width - 1;
	if (particle->m_x >= width)
		particle->m_x = 0;
	if (particle->m_y <= -1)
		particle->m_y = height - 1;
	if (particle->m_y >= height)
		particle->m_y = 0;
}

void iteration(
	boost::multi_array < unsigned int, 2 >& field,
	std::vector < std::shared_ptr < Particle > >& particles, 
	unsigned int width, unsigned int height)
{
	static std::random_device seed;
	static std::mt19937 engine(seed());
	static std::uniform_int_distribution< int > distribution(0, 3);

	for (auto i = particles.size() - 1; i > 0; --i)
	{
		field[particles[i]->m_x][particles[i]->m_y]--;
		switch (static_cast < Direction > (distribution(engine)))
		{
		case Direction::down:
			particles[i]->m_y++;
			break;
		case Direction::left:
			particles[i]->m_x--;
			break;
		case Direction::right:
			particles[i]->m_x++;
			break;
		case Direction::up:
			particles[i]->m_y--;
			break;
		default:
			break;
		}
		check_boundaries(particles[i], width, height);
		field[particles[i]->m_x][particles[i]->m_y]++;		
	}
}

int main(int argc, char** argv)
{
	const auto width = 300;
	const auto height = 300;

	sf::RenderWindow window(sf::VideoMode(width, height), "Brownian motion");

	const auto N = 1000U;
	std::vector < std::shared_ptr < Particle > > particles(N);

	for (auto i = 0U; i < N; ++i)
	{
		particles[i] = std::make_shared < Particle > (width / 2, height / 2);
	}

	sf::Image image;
	image.create(width, height, sf::Color::Black);

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	boost::multi_array < unsigned int, 2 > field (boost::extents[width][height]);
	field[width / 2][height / 2] = N;

	sf::Event event;

	std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();

	const std::chrono::microseconds delay(10000);

	std::chrono::microseconds timer(0);

	while (window.isOpen())
	{
		timer += std::chrono::duration_cast <std::chrono::microseconds> (
			std::chrono::steady_clock::now() - time_point);

		time_point = std::chrono::steady_clock::now();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (timer > delay)
		{
			timer = std::chrono::microseconds(0);
			iteration(field, particles, width, height);
		}

		for (auto x = 0U; x < width; ++x)
		{
			for (auto y = 0U; y < height; ++y)
			{
				if (field[x][y] != 0)
					image.setPixel(x, y, sf::Color(255, 0, 0, 255 - 255 / field[x][y]));
				else
					image.setPixel(x, y, sf::Color::Black);
			}
		}

		texture.update(image);

		window.draw(sprite);

		window.display();
	}

	system("pause");

	return EXIT_SUCCESS;
}
