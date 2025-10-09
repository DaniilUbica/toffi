#include "GamePointsController.h"

std::shared_ptr<GamePointsController> GamePointsController::instance() {
    if (const auto sp = m_instance.lock()) {
        return sp;
    }

    const auto sp = std::shared_ptr<GamePointsController>(new GamePointsController());
    m_instance = sp;

    return sp;
}

void GamePointsController::addPoints(int count) {
    m_points += count;
    fireGamePointsChanged(m_points);
}
