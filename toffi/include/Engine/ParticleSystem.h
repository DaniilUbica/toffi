#pragma once

#include <SFML/Graphics.hpp>

class Particle {
private:
	sf::CircleShape m_shape;
	sf::Vector2f    m_velocity;
	float           m_lifetime;

public:
	Particle(sf::Vector2f pos, sf::Color& color);

	void Update(float time);

	sf::CircleShape getShape() { return m_shape; };
	float getLifetime() { return m_lifetime; };
};

class ParticleSystem {
private:
	static ParticleSystem* m_instance;
	std::vector<Particle>  m_particles;

	ParticleSystem() = default;

public:
	ParticleSystem(const ParticleSystem&) = delete;
	void operator=(const ParticleSystem&) = delete;
	~ParticleSystem();

	static ParticleSystem* instance();
	void Update(float time);
	void burstingBubble(sf::Vector2f pos, const sf::Texture& texture);
	void drawParticles(sf::RenderWindow& window);
};
