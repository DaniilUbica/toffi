#include "Weapon.h"

class RangeWeapon : public Weapon {
private:
	std::vector<Bullet*> m_bullets;
	sf::Texture          m_bullet_texture;

public:
	RangeWeapon(const sf::Texture& bullet_texture, sf::Vector2f pos, float damage_scale, float reload_time);
	~RangeWeapon();

	void Update(float time, sf::Vector2f pos, std::vector<Character*>& characters) override;
	void Attack(sf::Vector2f direction) override;

	std::vector<Bullet*> getBullets() const;
};