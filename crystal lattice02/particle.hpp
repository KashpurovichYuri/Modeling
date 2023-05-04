#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:

	Particle() noexcept = default;

	explicit Particle(float x, float y, float radius, float mass, sf::Vector2f acceleration) noexcept :
		m_position(x, y), m_radius(radius), m_mass(mass),
		m_force(mass * acceleration), m_acceleration(acceleration),
		m_speed(sf::Vector2f(0.0f, 0.0f))
	{

	}

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

	const auto& getForce() const noexcept
	{
		return m_force;
	}

	const auto& getAcceleation() const noexcept
	{
		return m_acceleration;
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

	void setForce(sf::Vector2f force) noexcept
	{
		m_force = force;
	}

	void setAcceleration(sf::Vector2f acceleration)
	{
		m_acceleration = acceleration;
	}

public:

	void move(sf::Vector2f force) noexcept
	{
		m_force = force;
		m_position += m_speed * 0.1f + sf::Vector2f(m_force.x / m_mass * 0.1f * 0.01f, m_force.y / m_mass * 0.1f * 0.01f);
		m_speed += sf::Vector2f(m_force.x / m_mass * 0.1f, m_force.y / m_mass * 0.1f);
	}

private:

	sf::Vector2f m_position;

	float m_radius;
	float m_mass;
	
	sf::Vector2f m_acceleration;
	sf::Vector2f m_speed;
	sf::Vector2f m_force;
};