#include "GameOverScreen.h"

#include "Constants.h"

#include "Engine/Constants.h"

#include "Primitives/Text/Text.hpp"
#include "Primitives/RectangleShape/RectangleShape.hpp"

GameOverScreen::GameOverScreen() {
    using namespace game_engine::primitives;

    auto dimmer = std::make_shared<RectangleShape>(FloatRect(0.0, 0.0, WINDOW_WIDTH, WINDOW_HEIGHT));
    auto gameOverText = std::make_shared<Text>(game_engine::FONT, GAME_OVER_TEXT, GAME_OVER_TEXT_SIZE);
    auto gameOverRestartText = std::make_shared<Text>(game_engine::FONT, GAME_OVER_RESTART_TEXT, GAME_OVER_RESTART_TEXT_SIZE);

    dimmer->setFillColor(Color(0, 0, 0, 75));
    gameOverText->setFillColor(colors::White);
    gameOverRestartText->setFillColor(colors::White);

    addObject(dimmer);
    addObject(gameOverText);
    addObject(gameOverRestartText);
}
