#include "Weapon.h"

class RangeWeapon : public Weapon {
private:
	std::vector<std::shared_ptr<Bullet>> m_bullets;
	sf::Texture m_bullet_texture;

public:
	RangeWeapon(const sf::Texture& bullet_texture, sf::Vector2f pos, float damage_scale, float reload_time);
	~RangeWeapon() = default;

	void Update(float time, sf::Vector2f pos, std::vector<std::shared_ptr<Character>>& characters, float attack_range) override;
	void Attack() override;
	void shootConcreteBullet(std::shared_ptr<Bullet> bullet);

	std::vector<std::shared_ptr<Bullet>> getBullets() const;
};
