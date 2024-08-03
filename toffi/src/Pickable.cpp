#include "Engine/Pickable.h"

void Pickable::commonPicked() {
	m_picked = true;
}

bool Pickable::getPicked() {
	return m_picked;
}
