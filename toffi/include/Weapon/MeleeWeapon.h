#include "Weapon.h"

enum class AttackState {
	None,
	Attack,
	Return
};

class MeleeWeapon : public Weapon {
private:
	sf::Texture        m_texture;
	AttackState        m_attack_state;
    sf::Sprite         m_sprite;
	float 			   m_attack_speed = 0.5f;
	float			   m_return_speed = 0.2f;
	float			   m_attack_progress = 0.f;
	float			   m_attack_distance = 30.f;

public:
	MeleeWeapon(const sf::Texture& texture, sf::Vector2f pos, float damage_scale, float reload_time);
	~MeleeWeapon() = default;

	void Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<Character>>& characters, float attack_range) override;
	void Attack() override;

	sf::Sprite getWeapon() const;
};
