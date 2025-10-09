#include "GameInterfaceScreen.h"

#include "Constants.h"

#include "Controllers/GamePointsController.h"
#include "Controllers/ViewController.h"

void GameInterfaceScreen::constructScreen() {
    using namespace game_engine::primitives;

    m_gamePointsConntection = GamePointsController::instance()->fireGamePointsChanged.connect([this](int gamePoints) {
        m_pointsText->setText(std::to_string(gamePoints));
    });

    const auto gamePoints = GamePointsController::instance()->points();
    const auto viewPos = ViewController::instance()->getViewPos();
    m_pointsText = std::make_shared<Text>(game_engine::FONT, std::to_string(gamePoints), GAME_POINTS_TEXT_SIZE);
    m_pointsText->setFillColor(colors::White);
    m_pointsText->setPosition({ viewPos.x + GAME_POINTS_FROM_LEFT_OFFSET, viewPos.y + GAME_POINTS_FROM_TOP_OFFSET });

    m_primitivesDrawableObjects.push_back(std::make_pair(m_pointsText, false));
}

void GameInterfaceScreen::Update(float time) {
    const auto viewPos = ViewController::instance()->getViewPos();
    m_pointsText->setPosition({ viewPos.x + GAME_POINTS_FROM_LEFT_OFFSET, viewPos.y + GAME_POINTS_FROM_TOP_OFFSET });
}
