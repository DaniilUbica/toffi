#include "Engine/ParticleSystem.h"
#include "Engine/Constants.h"
#include "Engine/Helpers.hpp"

ParticleSystem* ParticleSystem::m_instance = nullptr;

Particle::Particle(sf::Vector2f pos, sf::Color& color) {
	m_shape.setPosition(pos.x, pos.y);
	m_shape.setRadius(PARTICLE_RADIUS);
	m_shape.setFillColor(color);

	float angle = static_cast<float>(std::rand()) / RAND_MAX * 2 * PI;
	float speed = static_cast<float>(std::rand()) / RAND_MAX * 100.0f;
	m_velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

	m_lifetime = 1.0f;
}

void Particle::Update(float time) { 
	m_shape.move(m_velocity * time);
	m_lifetime -= time;

	sf::Color color = m_shape.getFillColor();
	color.a = static_cast<sf::Uint8>(255 * (m_lifetime / 1.0f));
	m_shape.setFillColor(color);
}

ParticleSystem::~ParticleSystem() {
	m_instance = nullptr;
}

ParticleSystem* ParticleSystem::instance() {
	if (!m_instance) {
		m_instance = new ParticleSystem();
	}

	return m_instance;
}

void ParticleSystem::Update(float time) {
	for (auto& particle : m_particles) {
		particle.Update(time);

		auto iter = std::find_if(m_particles.begin(), m_particles.end(), [](Particle particle){
			return particle.getLifetime() <= 0;
		});
		if (iter != m_particles.end()) {
			m_particles.erase(iter);
		}
	}
}

void ParticleSystem::burstingBubble(sf::Vector2f pos, const sf::Texture& texture) {
	auto particle_color = calculateAverageTextureColor(texture);

	for (int i = 0; i < BURSTING_BUBBLE_PARTICLES_COUNT; i++) {
		m_particles.emplace_back(pos, particle_color);
	}
}

void ParticleSystem::drawParticles(sf::RenderWindow& window) {
	for (auto& particle : m_particles) {
		window.draw(particle.getShape());
	}
}
