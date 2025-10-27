#include "UpgradesScreen.h"

#include "Constants.h"
#include "Controllers/ViewController.h"

#include "Engine/Constants.h"

#include "Primitives/Text/Text.hpp"
#include "Primitives/RectangleShape/RectangleShape.hpp"

void UpgradesScreen::constructScreen() {
    using namespace game_engine::primitives;

    m_primitivesDrawableObjects.clear();

    auto dimmer = std::make_shared<RectangleShape>(FloatRect(0.0, 0.0, game_engine::WORLD_WIDTH, game_engine::WORLD_HEIGHT));
    auto tip = std::make_shared<Text>(game_engine::FONT, "SOME UPGRADES WILL BE PRESENTED HERE...", 72);

    dimmer->setFillColor(Color(0, 0, 0, 75));
    tip->setFillColor(colors::White);

    const auto viewPos = ViewController::instance()->getViewPos();
    const auto tipTextSize = tip->getLocalBounds().getSize();

    tip->setPosition({ viewPos.x + VIEW_WIDTH / 2 - tipTextSize.x / 2, viewPos.y + VIEW_HEIGHT / 2 - tipTextSize.y / 2 - 100 });

    m_primitivesDrawableObjects.push_back(std::make_pair(dimmer, false));
    m_primitivesDrawableObjects.push_back(std::make_pair(tip, false));
}
