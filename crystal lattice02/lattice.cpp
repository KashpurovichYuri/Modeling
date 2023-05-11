#include "lattice.hpp"

void Lattice::initialize() noexcept
{
	for (auto j = 0U; j < m_Nx; ++j)
	{
		for (auto i = 0U; i < m_Ny; ++i)
		{
			auto position = sf::Vector2f(i * m_connection_length, j * m_connection_length);

			m_particles.push_back(std::make_shared < Particle >(position, position, m_radius, m_mass, m_acceleration));
		}
	}

	const auto size = std::size(m_particles);

	for (auto i = 0U; i < size / m_Ny; ++i)
	{
		for (auto j = 0U; j < size / m_Nx - 1; ++j)
		{
			m_links.push_back(Link(particle(i * m_Ny + j), particle((i * m_Ny + j + 1)), 0.5f));
		}
	}

	for (auto i = 0U; i < size / m_Ny - 1; ++i)
	{
		for (auto j = 0U; j < size / m_Nx; ++j)
		{
			m_links.push_back(Link(particle(i * m_Ny + j), particle(((i + 1) * m_Ny + j)), 0.5f));
		}
	}

	for (auto i = 0U; i < size / m_Ny - 1; ++i)
	{
		for (auto j = 0U; j < size / m_Nx - 1; ++j)
		{
			m_links.push_back(Link(particle(i * m_Ny + j), particle(((i + 1) * m_Ny + j + 1)), 0.5f));
		}
	}

	for (auto i = 1U; i < size / m_Ny; ++i)
	{
		for (auto j = 0U; j < size / m_Nx - 1; ++j)
		{
			m_links.push_back(Link(particle(i * m_Ny + j), particle(((i - 1) * m_Ny + j + 1)), 0.5f));
		}
	}
}

void Lattice::push(const sf::Vector2f force) const noexcept
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(force);
	}
}

void Lattice::update() const noexcept
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(m_mass * m_acceleration);

		if (m_particles[i]->position().y + m_particles[i]->radius() > m_max_point.y)
		{
			m_particles[i]->set_y(m_max_point.y - m_particles[i]->radius());
		}

		if (m_particles[i]->position().y - m_particles[i]->radius() < m_min_point.y)
		{
			m_particles[i]->set_y(m_min_point.y + m_particles[i]->radius());
		}

		if (m_particles[i]->position().x + m_particles[i]->radius() > m_max_point.x)
		{
			m_particles[i]->set_x(m_max_point.x - m_particles[i]->radius());
		}

		if (m_particles[i]->position().x - m_particles[i]->radius() < m_min_point.x)
		{
			m_particles[i]->set_x(m_min_point.x + m_particles[i]->radius());
		}
	}

	for (auto i = 0U; i < std::size(m_links); ++i)
	{
		m_links[i].update();
	}
}