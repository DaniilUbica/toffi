#include "Weapon/MeleeWeapon.h"
#include "Engine/Character.h"

MeleeWeapon::MeleeWeapon(const sf::Texture& texture, sf::Vector2f pos, float damage_scale, float reload_time) {
	m_texture = texture;
	m_pos = pos;
	m_damage_scale = damage_scale;
	m_reload_time = reload_time;
	m_weapon_type = WeaponType::MELEE;
	m_reload_timer = std::make_unique<Timer>(m_reload_time);

	m_weapon.setSize(sf::Vector2f(20.f, 10.f));
	m_weapon.setFillColor(sf::Color::Green);
}

void MeleeWeapon::Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<Character>>& characters, float attack_range) {
	Weapon::commonUpdate(pos, characters, attack_range);

	m_pos = pos;

	m_weapon.setPosition(m_pos);
	m_weapon.setRotation(m_angle);
}

void MeleeWeapon::Attack() {

}

sf::RectangleShape MeleeWeapon::getWeapon() const {
	return m_weapon;
}
