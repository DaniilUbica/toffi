#include "Currency.h"

#include "Controllers/CashValueController.h"

Currency::Currency(std::shared_ptr<game_engine::Character> character, const game_engine::primitives::Texture& texture, game_engine::primitives::Vector2f pos, unsigned int valueToAdd) : game_engine::Pickable(character, texture, pos, true) {
    m_valueToAdd = valueToAdd;
}

void Currency::onPicked() {
    game_engine::Pickable::commonPicked();
    CashValueController::instance()->addCash(m_valueToAdd);
}
