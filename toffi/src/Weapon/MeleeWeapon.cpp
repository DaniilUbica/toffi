#include "Weapon/MeleeWeapon.h"
#include "Engine/Base/Character.h"
#include "Engine/Constants.h"
#include "Constants.h"

std::shared_ptr<game_engine::Character> MeleeWeapon::checkCollisionWithCharacters(std::vector<std::shared_ptr<game_engine::Character>>& characters) {
    for (const auto character : characters) {
        if (character->getSprite()->getGlobalBounds().findIntersection(m_sprite->getGlobalBounds())) {
            return character;
        }
    }

    return nullptr;
}

MeleeWeapon::MeleeWeapon(const sf::Texture& texture, sf::Vector2f pos, float damage_scale, float reload_time, std::weak_ptr<game_engine::Character> parent) {
	m_texture = texture;
	m_pos = pos;
    m_damage = MELEE_WEAPON_DEFAULT_DAMAGE;
	m_damage_scale = damage_scale;
	m_reload_time = reload_time;
	m_weapon_type = WeaponType::MELEE;
	m_reload_timer = std::make_unique<game_engine::Timer>(m_reload_time);
    m_sprite = std::make_shared<sf::Sprite>(m_texture);
    m_parent = parent;

    m_sprite->setOrigin({ 0, static_cast<float>(texture.getSize().y / 2) });
    m_sprite->setScale({ 0.05, 0.05 });
}

void MeleeWeapon::Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) {
	Weapon::commonUpdate(pos, characters, attack_range);

	m_pos = pos;

    if (const auto sp = m_parent.lock()) {
        const auto parentDirection = sp->getDirection();
        if (parentDirection == game_engine::Direction::LEFT) {
            if (m_direction.x <= 0) {
                m_angle = std::atan2(m_direction.y, m_direction.x) * 180 / game_engine::PI;
            }
            else {
                m_angle = -180.f;
            }
        }
        else if (parentDirection == game_engine::Direction::RIGHT) {
            m_pos = { m_pos.x + sp->getSize().x, m_pos.y };
            if (m_direction.x >= 0) {
                m_angle = std::atan2(m_direction.y, m_direction.x) * 180 / game_engine::PI;
            }
            else {
                m_angle = 0.f;
            }
        }
    }

	int attack_progress_coeff = m_attack_state == AttackState::Attack ? 1 : -1;
	if (m_attack_state == AttackState::Attack) {
		m_attack_progress += m_attack_speed * time;
        if (const auto character = checkCollisionWithCharacters(characters)) {
            character->takeDamage(m_damage);
        }

        if (m_attack_progress >= 1.f) {
            m_attack_state = AttackState::Return;
        }
	}
	else if (m_attack_state == AttackState::Return) {
		m_attack_progress += m_return_speed * time;

        if (m_attack_progress <= 0.f) {
            m_attack_state = AttackState::None;
            m_attack_progress = 0.f;
        }
	}

    m_sprite->setPosition({ m_pos.x, m_pos.y });
    m_sprite->setRotation(sf::degrees(m_angle));
}

void MeleeWeapon::Attack() {
	if (m_gotEnemyInAttackRange && !m_reload_timer->isRunning()) {
		m_attack_state = AttackState::Attack;
        m_attack_progress = 0.f;
        m_reload_timer->Start();
	}
	else {
		m_attack_state = AttackState::None;
	}
}

std::shared_ptr<sf::Sprite> MeleeWeapon::getWeapon() const {
	return m_sprite;
}
