#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "particle.hpp"

class Link
{
public:

	using particle_t = std::shared_ptr < Particle >;

public:

	Link() noexcept = default;

	explicit Link(particle_t particle_1, particle_t particle_2, float stiffness) noexcept :
		m_particle_1(particle_1), m_particle_2(particle_2), m_stiffness(stiffness),
		m_distance(length(m_particle_1->position() - m_particle_2->position()))
	{
		calculateDelta();

		calculateMaxDistance();
	}

	~Link() noexcept = default;

private:

	void calculateMaxDistance() noexcept
	{
		if (m_particle_1 != m_particle_2)
			m_max_distance = m_distance - m_particle_1->getForce().y / m_stiffness;
		else
			m_distance = 0.0f;
	}

	void calculateDelta() noexcept
	{
		if (m_particle_1 != m_particle_2)
			m_delta = m_particle_1->getForce() / m_stiffness;
		else
			m_delta = sf::Vector2f (0.0f, 0.0f);
	}

public:

	auto getDistance() const noexcept
	{
		return m_distance;
	}

	auto getStiffness() const noexcept
	{
		return m_stiffness;
	}

	auto getMaxDistance() const noexcept
	{
		return m_max_distance;
	}

	void update() noexcept
	{
		if (m_max_distance < length(m_particle_1->position() - m_particle_2->position()))
			m_distance = m_max_distance;
		else
			m_distance = length(m_particle_1->position() - m_particle_2->position());
	}

	const auto& getDelta() const noexcept
	{
		return m_delta;
	}

private:

	particle_t m_particle_1;
	particle_t m_particle_2;

	float m_stiffness;
	float m_distance;
	float m_max_distance;
	sf::Vector2f m_delta;
};