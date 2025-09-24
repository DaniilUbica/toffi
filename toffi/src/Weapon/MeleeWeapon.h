#pragma once

#include "Weapon.h"

enum class AttackState {
	None,
	Attack,
	Return
};

class MeleeWeapon : public Weapon {
private:
    AttackState                 m_attack_state;
    float                       m_damage;
    float                       m_angle = 1.f;
    float                       m_attack_speed = 0.005f;
    float                       m_weapon_move_to_pos_speed = 0.2f;
    float                       m_attack_progress = 0.f;
    float                       m_attack_distance = 30.f;
    bool                        m_returning_weapon_to_start = false;

    std::weak_ptr<game_engine::Character> m_parent;

    std::shared_ptr<game_engine::Character> checkCollisionWithCharacters(std::vector<std::shared_ptr<game_engine::Character>>& characters);
    std::pair<game_engine::primitives::Vector2f, float> calculateTargetPositionAndAngle(const game_engine::primitives::Vector2f& parent_center, float parent_offset, std::shared_ptr<game_engine::Character> nearest_character);
    void moveToTarget(const game_engine::primitives::Vector2f& target_pos, float delta_time);
    void rotateToTarget(float target_angle, float delta_time);
    void handleAttackState(std::vector<std::shared_ptr<game_engine::Character>>& characters, float delta_time);

    void attackIfCanAttack() override;

public:
	MeleeWeapon(const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos, float damage_scale, float reload_time, std::weak_ptr<game_engine::Character> parent);
	~MeleeWeapon() = default;

	void Update(float time, game_engine::primitives::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) override;
};
