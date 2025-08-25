#include "Weapon/MeleeWeapon.h"
#include "Character.h"

MeleeWeapon::MeleeWeapon(const sf::Texture& texture, sf::Vector2f pos, float damage_scale, float reload_time) {
	m_texture = texture;
	m_pos = pos;
	m_damage_scale = damage_scale;
	m_reload_time = reload_time;
	m_weapon_type = WeaponType::MELEE;
	m_reload_timer = std::make_unique<Timer>(m_reload_time);
    m_sprite = std::make_shared<sf::Sprite>(m_texture);

    m_sprite->setScale({ 0.1, 0.1 });
}

void MeleeWeapon::Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<Character>>& characters, float attack_range) {
	Weapon::commonUpdate(pos, characters, attack_range);

	m_pos = pos;

	int attack_progress_coeff = m_attack_state == AttackState::Attack ? 1 : -1;
	if (m_attack_state == AttackState::Attack && m_attack_progress < m_attack_distance) {
		m_attack_progress += m_attack_speed * time;
	}
	else if (m_attack_state == AttackState::Return) {
		m_attack_progress += m_return_speed * time;
	}

    m_sprite->setPosition({ m_pos.x, m_pos.y });
    m_sprite->setRotation(sf::radians(m_angle));
}

void MeleeWeapon::Attack() {
	if (m_gotEnemyInAttackRange) {
		m_attack_state = AttackState::Attack;
	}
	else {
		m_attack_state = AttackState::None;
	}
}

std::shared_ptr<sf::Sprite> MeleeWeapon::getWeapon() const {
	return m_sprite;
}
