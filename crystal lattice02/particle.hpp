#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:

	Particle() noexcept = default;

	explicit Particle(sf::Vector2f position, sf::Vector2f previous_position,
		float radius, float mass, sf::Vector2f acceleration) noexcept :
			m_position(position), m_previous_position(previous_position),
			m_acceleration(acceleration), m_radius(radius), m_mass(mass)
	{}

	~Particle() noexcept = default;

public:

	const auto position() const noexcept 
	{ 
		return m_position; 
	}

	const auto radius() const noexcept
	{
		return m_radius;
	}

public:

	void set_x(float x) noexcept
	{
		m_position.x = x;
	}

	void set_y(float y) noexcept
	{
		m_position.y = y;
	}

public:

	void move(sf::Vector2f delta) noexcept
	{
		m_position += delta;
	}

private:

	sf::Vector2f m_position;
	sf::Vector2f m_previous_position;
	sf::Vector2f m_acceleration;

	float m_radius;
	float m_mass;
};