#include "Weapon/Weapon.h"
#include "Engine/Base/Character.h"
#include "Constants.h"

float Weapon::distance(sf::Vector2f v1, sf::Vector2f v2) {
	return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

bool Weapon::compareDistance(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f target) {
	return distance(v1, target) < distance(v2, target);
}

bool Weapon::isInAttackRange(sf::Vector2f pos, std::shared_ptr<game_engine::Character> character, float range) {
	sf::Vector2f char_pos = character->getPosition();

	if (abs(char_pos.x - pos.x) <= range || abs(char_pos.y - pos.y) <= range) {
		return true;
	}

	return false;
}

void Weapon::commonUpdate(sf::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) {
	if (!characters.empty()) {
		auto nearest = std::min_element(characters.begin(), characters.end(), [this](std::shared_ptr<game_engine::Character> c1, std::shared_ptr<game_engine::Character> c2) {
			return compareDistance(c1->getPosition(), c2->getPosition(), m_pos);
		});

		if (nearest != characters.end() && *nearest) {
			sf::Vector2f nearest_character_pos = (*nearest)->getPosition();

			m_direction = nearest_character_pos - m_pos;
			m_angle = std::atan2(m_direction.y, m_direction.x) * 180 / game_engine::PI;
			m_direction /= static_cast<float>(sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y));
			m_gotEnemyInAttackRange = isInAttackRange(m_pos, *nearest, attack_range);
		}
	}
}

void Weapon::updateAttackSpeed(float scale) {
    m_reload_time *= scale;
}

WeaponType Weapon::getWeaponType() const {
    return m_weapon_type;
}
