#include "../include/Weapon/Weapon.h"

void Weapon::updateAttackSpeed(float scale) {
    m_reload_time *= scale;
}

WeaponType Weapon::getWeaponType() const {
    return m_weapon_type;
}
