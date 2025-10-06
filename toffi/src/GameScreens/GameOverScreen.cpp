#include "GameOverScreen.h"

#include "Constants.h"
#include "Controllers/ViewController.h"

#include "Engine/Constants.h"

#include "Primitives/Text/Text.hpp"
#include "Primitives/RectangleShape/RectangleShape.hpp"

void GameOverScreen::constructScreen() {
    using namespace game_engine::primitives;

    m_primitivesDrawableObjects.clear();

    auto dimmer = std::make_shared<RectangleShape>(FloatRect(0.0, 0.0, game_engine::WORLD_WIDTH, game_engine::WORLD_HEIGHT));
    auto gameOverText = std::make_shared<Text>(game_engine::FONT, GAME_OVER_TEXT, GAME_OVER_TEXT_SIZE);
    auto gameOverRestartText = std::make_shared<Text>(game_engine::FONT, GAME_OVER_RESTART_TEXT, GAME_OVER_RESTART_TEXT_SIZE);

    dimmer->setFillColor(Color(0, 0, 0, 75));
    gameOverText->setFillColor(colors::White);
    gameOverRestartText->setFillColor(colors::White);

    const auto viewPos = ViewController::instance()->getViewPos();
    const auto gameOverTextSize = gameOverText->getLocalBounds().getSize();
    const auto gameOverRestartTextSize = gameOverRestartText->getLocalBounds().getSize();

    gameOverText->setPosition({ viewPos.x + VIEW_WIDTH / 2 - gameOverTextSize.x / 2, viewPos.y + VIEW_HEIGHT / 2 - gameOverTextSize.y / 2 - GAME_OVER_TEXT_Y_OFFSET });
    gameOverRestartText->setPosition({ viewPos.x + VIEW_WIDTH / 2 - gameOverRestartTextSize.x / 2, viewPos.y + VIEW_HEIGHT / 2 - gameOverRestartTextSize.y / 2 - GAME_OVER_RESTART_TEXT_Y_OFFSET });

    m_primitivesDrawableObjects.push_back(std::make_pair(dimmer, false));
    m_primitivesDrawableObjects.push_back(std::make_pair(gameOverText, false));
    m_primitivesDrawableObjects.push_back(std::make_pair(gameOverRestartText, false));
}

void GameOverScreen::setAllScreenObjectsVisible(bool visible) {
    for (auto& pair : m_primitivesDrawableObjects) {
        pair.second = visible;
    }
}

void GameOverScreen::draw(const game_engine::primitives::RenderWindow &window) {
    for (auto& pair : m_primitivesDrawableObjects) {
        pair.first->draw(window);
    }
}

