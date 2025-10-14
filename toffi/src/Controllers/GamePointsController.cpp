#include "GamePointsController.h"

void GamePointsController::addPoints(int count) {
    m_points += count;
    fireGamePointsChanged(m_points);
}
