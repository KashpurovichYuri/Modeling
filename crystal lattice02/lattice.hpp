#pragma once

#include <iostream>

#include "functions.hpp"
#include "particle.hpp"
#include "link.hpp"


class Latice
{
private:

	using particle_t = std::shared_ptr < Particle >;

public:

	explicit Latice(
		unsigned int width,
		unsigned int height,
		float length,
		float r,
		float m,
		float stifness,
		const std::string& type = "Rectangle") noexcept :
		m_min_point(0.0f, 0.0f),
		m_max_point(775.0f, 575.0f),
		m_connection_length(length),
		m_connection_length_p(static_cast < unsigned int > (length)),
		m_Nx(width / length),
		m_Ny(height / length),
		m_r(r),
		m_mass(m),
		m_stifness(stifness),
		m_type(type)
	{
		m_force = sf::Vector2f(0.0f, m_g);

		create_lattice();

		create_links();

		calculateLimitHeights();
	}

	~Latice() noexcept = default;

private:

	void create_lattice() noexcept // order is important: matrix
	{
		for (auto j = 0; j < m_max_point.x; j += m_connection_length_p)
			for (auto i = 0; i < m_max_point.y; i += m_connection_length_p)
				m_particles.push_back(
					std::make_shared < Particle >(j, i, m_r, m_mass, m_force));
	}

	void create_links() noexcept // actually y-links for one column (because structure is periodic)
	{
		for (auto i = 1U; i < m_Ny; ++i)
		{
			m_links.push_back(Link(getIndexedParticle(i - 1), getIndexedParticle(i), m_stifness));
			m_particles[i]->setForce(m_particles[i - 1]->getForce() + m_stifness * m_links.back().getDelta());
			//std::cerr << m_links.back().getDelta().y << " " << i << " " << m_Ny << "\n";
		}
	}

	void calculateLimitHeights() noexcept
	{
		auto height = 0.0f;

		for (int i = m_Ny - 2; i >= 0; --i)
		{
			m_limit_heights.push_back(m_max_point.y - height);

			height += m_links[i].getMaxDistance();

			//std::cerr << "height: " << height << " " << m_limit_heights.back() << "\n";
		}
		m_limit_heights.push_back(m_max_point.y - height);

		std::reverse(std::begin(m_limit_heights), std::end(m_limit_heights));

	}

public:

	auto getParticlesSize() const noexcept
	{
		return m_particles.size();
	}

	auto getParticlesRad() const noexcept
	{
		return m_r;
	}

	particle_t& getIndexedParticle(unsigned int ind) noexcept
	{
		return m_particles.at(ind);
	}

	void update() noexcept
	{
		for (auto i = 0U; i < std::size(m_particles); ++i)
		{
			m_particles[i]->move(sf::Vector2f(0.0f, m_mass * m_g));
		
			if (m_particles[i]->position().y + m_particles[i]->radius() > m_limit_heights[i % m_Ny])
			{
				m_particles[i]->set_y(m_limit_heights[i % m_Ny] - m_particles[i]->radius());
			}
		}

		for (auto i = 0U; i < std::size(m_links); ++i)
		{
			m_links[i].update();
		}

	}

private:

	static inline const auto m_g = 10.0f;

private:

	sf::Vector2f m_min_point;
	sf::Vector2f m_max_point;

	unsigned int m_Nx;
	unsigned int m_Ny;
	float m_connection_length;
	unsigned int m_connection_length_p;
	float m_r;
	float m_mass;
	float m_stifness;
	sf::Vector2f m_force;
	std::string m_type;

	std::vector < particle_t > m_particles;
	std::vector < Link > m_links;
	std::vector < float > m_limit_heights;
};