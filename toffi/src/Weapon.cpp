#include "../include/Weapon/Weapon.h"

Weapon::~Weapon() {
    delete m_reload_timer;
}

void Weapon::updateAttackSpeed(float scale) {
    m_reload_time *= scale;
}

WeaponType Weapon::getWeaponType() const {
    return m_weapon_type;
}
