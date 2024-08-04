#include "Textures.h"

TextureHolder* TextureHolder::m_texture_holder = nullptr;

TextureHolder::~TextureHolder() {
	m_texture_holder = nullptr;
}

TextureHolder* TextureHolder::instance() {
	if (m_texture_holder == nullptr) {
		m_texture_holder = new TextureHolder();
	}

	return m_texture_holder;
}

void TextureHolder::setTextures() {
	m_player_textures[State::IDLE].loadFromFile("idle.png");
	m_player_textures[State::RUN].loadFromFile("run.png");

	m_lvl1_border_texture.loadFromFile("border.png");
	m_lvl1_background_texture.loadFromFile("background.png");

	m_flying_eye_texture.loadFromFile("eye_flight.png");
	m_spider_texture.loadFromFile("spider.png");

	m_bullet_texture.loadFromFile("bullet.png");
    m_sword_texture.loadFromFile("sword.png");

	m_heal_texture.loadFromFile("heart.png");
}
