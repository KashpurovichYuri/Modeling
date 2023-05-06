#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "link.hpp"
#include "particle.hpp"

class Lattice
{
public:

	using particle_t = std::shared_ptr < Particle > ;

public:

	explicit Lattice(
		sf::Vector2f min_point, sf::Vector2f max_point,
		unsigned int Nx, unsigned int Ny,
		float length, float radius,
		float mass, float stiffness,
		sf::Vector2f acceleration)
		noexcept :
		m_min_point(min_point), m_max_point(max_point), 
		m_Nx(Nx), m_Ny(Ny),
		m_connection_length(length), m_radius(radius),
		m_mass(mass), m_stiffness(stiffness),
		m_acceleration(acceleration)
	{
		initialize();
	}

	~Lattice() noexcept = default;

private:

	void initialize() noexcept;

public:

	particle_t particle(std::size_t index) const noexcept
	{
		return m_particles.at(index);
	}

	const auto & particles() const noexcept
	{
		return m_particles;
	}

public:
	
	void push(sf::Vector2f force) const noexcept;

	void update() const noexcept;

private:

	sf::Vector2f m_min_point;
	sf::Vector2f m_max_point;

	unsigned int m_Nx;
	unsigned int m_Ny;

	float m_connection_length;
	float m_radius;
	float m_mass;
	float m_stiffness;
	
	sf::Vector2f m_acceleration;

	std::vector < particle_t > m_particles;

	std::vector < Link > m_links;
};