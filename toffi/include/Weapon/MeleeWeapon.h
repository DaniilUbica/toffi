#include "Weapon.h"

class MeleeWeapon : public Weapon {
private:
	sf::Texture m_texture;
	sf::RectangleShape m_weapon;

public:
	MeleeWeapon(const sf::Texture& texture, sf::Vector2f pos, float damage_scale, float reload_time);
	~MeleeWeapon() = default;

	void Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<Character>>& characters, float attack_range) override;
	void Attack() override;

	sf::RectangleShape getWeapon() const;
};
