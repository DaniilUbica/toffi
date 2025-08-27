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
    float                       m_return_speed = 0.2f;
    float                       m_attack_progress = 0.f;
    float                       m_attack_distance = 30.f;
    
    std::weak_ptr<game_engine::Character> m_parent;

    std::shared_ptr<game_engine::Character> checkCollisionWithCharacters(std::vector<std::shared_ptr<game_engine::Character>>& characters);

public:
	MeleeWeapon(const sf::Texture& texture, sf::Vector2f pos, float damage_scale, float reload_time, std::weak_ptr<game_engine::Character> parent);
	~MeleeWeapon() = default;

	void Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<game_engine::Character>>& characters, float attack_range) override;
	void Attack() override;

    std::shared_ptr<sf::Sprite> getWeapon() const;
};
