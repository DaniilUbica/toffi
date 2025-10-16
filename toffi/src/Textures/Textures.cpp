#include "Textures.h"

void TextureHolder::setTextures() {
    assert(m_player_textures[State::IDLE].loadFromFile("idle.png"));
    assert(m_player_textures[State::RUN].loadFromFile("run.png"));

    assert(m_lvl1_border_texture.loadFromFile("border.png"));
    assert(m_lvl1_background_texture.loadFromFile("background.png"));

    assert(m_flying_eye_texture.loadFromFile("eye_flight.png"));
    assert(m_spider_texture.loadFromFile("spider.png"));

    assert(m_bullet_texture.loadFromFile("bullet.png"));
    assert(m_sword_texture.loadFromFile("sword.png"));

    assert(m_heal_texture.loadFromFile("heart.png"));
    assert(m_coin_texture.loadFromFile("coin.png"));
}
