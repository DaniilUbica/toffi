#include "Weapon.h"

enum class AttackState {
	None,
	Attack,
	Return
};

class MeleeWeapon : public Weapon {
private:
    sf::Texture                 m_texture;
    AttackState                 m_attack_state;
    std::shared_ptr<sf::Sprite> m_sprite;
    float                       m_damage;
    float                       m_angle = 1.f;
    float                       m_attack_speed = 0.005f;
    float                       m_weapon_move_to_pos_speed = 0.2f;
    float                       m_attack_progress = 0.f;
    float                       m_attack_distance = 30.f;
    bool                        m_returning_weapon_to_start = false;

    std::weak_ptr<game_engine::Character> m_parent;

    std::shared_ptr<game_engine::Character> checkCollisionWithCharacters(std::vector<std::shared_ptr<game_engine::Character>>& characters);
    std::pair<sf::Vector2f, float> calculateTargetPositionAndAngle(const sf::Vector2f& parent_center, float parent_offset, std::shared_ptr<game_engine::Character> nearest_character);
    void moveToTarget(const sf::Vector2f& target_pos, float delta_time);
    void rotateToTarget(float target_angle, float delta_time);
    void handleAttackState(std::vector<std::shared_ptr<game_engine::Character>>& characters, float delta_time);

    void attackIfCanAttack() override;

public:
	MeleeWeapon(const sf::Texture& texture, sf::Vector2f pos, float damage_scale, float reload_time, std::weak_ptr<game_engine::Character> parent);
	~MeleeWeapon() = default;

	void Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) override;

    std::shared_ptr<sf::Sprite> getWeapon() const;
};
