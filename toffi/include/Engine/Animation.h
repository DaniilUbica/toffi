#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Animation {
private:
	std::vector<sf::IntRect> m_frames, m_rotated_frames;
	float m_current_frame, m_animation_speed;
	sf::Sprite m_sprite;

public:
	Animation() = delete;

	/// x and y is positions of texture in tileset
	Animation(const sf::Texture& texture, int x, int y, int width, int height, int frames_count, float animation_speed, int step);
	~Animation() = default;

	sf::Sprite Tick(float time, bool rotate);
};