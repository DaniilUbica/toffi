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
	Animation(sf::Texture& texture, int x, int y, int width, int height, int frames_count, float animation_speed, int step);

	sf::Sprite Tick(float time, bool rotate);
};