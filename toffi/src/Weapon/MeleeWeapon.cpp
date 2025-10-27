#include "Weapon/MeleeWeapon.h"
#include "Engine/Base/Character.h"
#include "Engine/Constants.h"
#include "Constants.h"

std::shared_ptr<game_engine::Character> MeleeWeapon::checkCollisionWithCharacters(std::vector<std::shared_ptr<game_engine::Character>>& characters) {
    for (const auto character : characters) {
        if (character->getSprite()->getGlobalBounds().intersects(m_sprite->getGlobalBounds())) {
            return character;
        }
    }

    return nullptr;
}

std::pair<game_engine::primitives::Vector2f, float> MeleeWeapon::calculateTargetPositionAndAngle(const game_engine::primitives::Vector2f& parent_center, float parent_offset, std::shared_ptr<game_engine::Character> nearest_character) {

    game_engine::primitives::Vector2f target_pos = parent_center + game_engine::primitives::Vector2f(parent_offset, 0.0);
    float target_angle = 0.f;

    if (nearest_character) {
        target_angle = std::atan2(m_direction.y, m_direction.x) * 180 / game_engine::PI;
        target_pos = parent_center + m_direction * parent_offset;
    }

    return { target_pos, target_angle };
}

void MeleeWeapon::moveToTarget(const game_engine::primitives::Vector2f& target_pos, float delta_time) {
    game_engine::primitives::Vector2f direction_to_target = target_pos - m_pos;
    float distance_to_target = static_cast<float>(sqrt(direction_to_target.x * direction_to_target.x + direction_to_target.y * direction_to_target.y));

    if (distance_to_target > 0) {
        direction_to_target /= distance_to_target;
        if (distance_to_target <= m_weapon_move_to_pos_speed * delta_time) {
            m_pos = target_pos;
        }
        else {
            m_pos += direction_to_target * m_weapon_move_to_pos_speed * delta_time;
        }
    }
}

void MeleeWeapon::rotateToTarget(float target_angle, float delta_time) {
    float angle_diff = target_angle - m_angle;

    if (angle_diff > 180.f) {
        angle_diff -= 360.f;
    }
    if (angle_diff < -180.f) {
        angle_diff += 360.f;
    }

    if (std::abs(angle_diff) <= m_weapon_move_to_pos_speed * delta_time) {
        m_angle = target_angle;
    }
    else {
        m_angle += (angle_diff > 0 ? 1 : -1) * m_weapon_move_to_pos_speed * delta_time;
    }
}

void MeleeWeapon::handleAttackState(std::vector<std::shared_ptr<game_engine::Character>>& characters, float delta_time) {
    if (m_attack_state == AttackState::Attack) {
        m_attack_progress += m_attack_speed * delta_time;
        if (const auto character = checkCollisionWithCharacters(characters)) {
            character->takeDamage(m_damage);
        }

        if (m_attack_progress >= 1.f) {
            m_attack_state = AttackState::Return;
        }
    }
    else if (m_attack_state == AttackState::Return) {
        m_attack_progress += m_weapon_move_to_pos_speed * delta_time;

        if (m_attack_progress <= 0.f) {
            m_attack_state = AttackState::None;
            m_attack_progress = 0.f;
        }
    }
}

MeleeWeapon::MeleeWeapon(const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos, float damage_scale, float reload_time, std::weak_ptr<game_engine::Character> parent) : Weapon(pos, damage_scale, reload_time, texture) {
    m_damage = MELEE_WEAPON_DEFAULT_DAMAGE;
    m_weapon_type = WeaponType::MELEE;
    m_parent = parent;

    m_sprite->setOrigin({ 0, static_cast<float>(texture.getSize().y / 2) });
    m_sprite->setScale({ 0.05, 0.05 });
}

void MeleeWeapon::Update(float time, game_engine::primitives::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) {

    const auto parent = m_parent.lock();
    if (!parent) {
        return;
    }

    Weapon::commonUpdate(pos, characters, m_sprite->getGlobalBounds().getSize().x);

    const auto parent_center_pos = parent->getPosition() + parent->getSprite()->getGlobalBounds().getSize() / 2.f;
    const auto parent_bounds = parent->getSprite()->getGlobalBounds();
    const auto parent_radius = std::max(parent_bounds.getSize().x, parent_bounds.getSize().y) / 2.0f;

    const float offset_distance = parent_radius + 20.0f;
    const auto nearest = getNearestCharacter(characters);

    if (nearest) {
        const auto nearest_character_pos = nearest->getPosition();
        m_direction = nearest_character_pos - parent_center_pos;
        m_direction /= static_cast<float>(sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y));
    }

    const auto [target_pos, target_angle] = calculateTargetPositionAndAngle(parent_center_pos, offset_distance, nearest);

    moveToTarget(target_pos, time);
    rotateToTarget(target_angle, time);

    m_sprite->setPosition({ m_pos.x, m_pos.y });
    m_sprite->setRotation(m_angle);

    handleAttackState(characters, time);

    attackIfCanAttack();
}

void MeleeWeapon::attackIfCanAttack() {
	if (m_gotEnemyInAttackRange && !m_reload_timer->running()) {
		m_attack_state = AttackState::Attack;
        m_attack_progress = 0.f;
        m_reload_timer->Restart();
	}
	else {
		m_attack_state = AttackState::None;
	}
}

