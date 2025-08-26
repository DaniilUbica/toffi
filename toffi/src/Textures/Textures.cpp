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
    bool textures_load_result = false;

    textures_load_result = m_player_textures[State::IDLE].loadFromFile("idle.png");
    textures_load_result = m_player_textures[State::RUN].loadFromFile("run.png");

    textures_load_result = m_lvl1_border_texture.loadFromFile("border.png");
    textures_load_result = m_lvl1_background_texture.loadFromFile("background.png");

    textures_load_result = m_flying_eye_texture.loadFromFile("eye_flight.png");
    textures_load_result = m_spider_texture.loadFromFile("spider.png");

    textures_load_result = m_bullet_texture.loadFromFile("bullet.png");
    textures_load_result = m_sword_texture.loadFromFile("sword.png");

    textures_load_result = m_heal_texture.loadFromFile("heart.png");

    assert(textures_load_result);
}
