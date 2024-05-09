#include "../include/Engine/Animation.h"

Animation::Animation(const sf::Texture& texture, int x, int y, int width, int height, int frames_count, float animation_speed, int step) {
    m_animation_speed = animation_speed;
    m_sprite.setTexture(texture);
    m_current_frame = 0;

    for (int i = 0; i < frames_count; i++) {
        m_frames.push_back(sf::IntRect(x + i * step, y, width, height));
    }

    for (int i = 0; i < frames_count; i++) {
        m_rotated_frames.push_back(sf::IntRect(x + i * step + width, y, -width, height));
    }
}

sf::Sprite Animation::Tick(float time, bool rotate) {
    m_current_frame += m_animation_speed * time;

    if (m_current_frame > float(m_frames.size())) {
        m_current_frame -= m_frames.size();
    }

    int i = m_current_frame;
    m_sprite.setTextureRect(m_frames[i]);

    if (!rotate) {
        m_sprite.setTextureRect(m_frames[i]);
    }
    if (rotate) {
        m_sprite.setTextureRect(m_rotated_frames[i]);
    }

    return m_sprite;
}
