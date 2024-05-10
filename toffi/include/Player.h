#pragma once

#include "Engine/Character.h"
#include "Engine/PlayerController.h"

class PlayerController;
class Weapon;

enum class WeaponType;

enum class State {
    IDLE,
    RUN
};

using textures_t = std::map<State, sf::Texture>;

class Player : public Character {
private:
	std::unique_ptr<PlayerController> m_controller;
	std::unique_ptr<Animation>        m_idle_animation;
	std::shared_ptr<Weapon>           m_weapon;
    State                             m_state;
    float                             m_attack_speed_scale = 1.0;
    float                             m_attack_range_scale = 1.0;

    void checkCollisionWithMapBorders();

public:
    Player() = delete;
    Player(const textures_t& textures, sf::Vector2f start_pos, float health);
    ~Player() = default;

    void Update(float time) override;
    void attackEnemies(float time, std::vector<std::shared_ptr<Character>>& characters);
    void initWeapon(WeaponType weapon_type, float damage_scale, const sf::Texture& bullet_texture = sf::Texture());

    void setState(State state);

    std::shared_ptr<Weapon> getWeapon() const;
};
