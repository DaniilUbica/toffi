#include "../include/Textures.h"

TextureHolder* TextureHolder::m_texture_holder = nullptr;

TextureHolder* TextureHolder::instance() {
	if (m_texture_holder == nullptr) {
		m_texture_holder = new TextureHolder();
	}

	return m_texture_holder;
}

void TextureHolder::setTextures() {
	m_player_textures[State::IDLE].loadFromFile("./Assets/player/idle.png");
	m_player_textures[State::RUN].loadFromFile("./Assets/player/run.png");

	m_lvl1_border_texture.loadFromFile("./Assets/level_1/border.png");
	m_lvl1_background_texture.loadFromFile("./Assets/level_1/background.png");

	m_flying_eye_texture.loadFromFile("./Assets/enemies/eye_flight.png");

	m_bullet_texture.loadFromFile("./Assets/bullet.png");
}
