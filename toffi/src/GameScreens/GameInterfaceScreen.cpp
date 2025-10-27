#include "GameInterfaceScreen.h"

#include "Constants.h"

#include "Engine/TimersHolder.hpp"
#include "Engine/GameStateMachine.h"

#include "Controllers/CashValueController.h"
#include "Controllers/GamePointsController.h"
#include "Controllers/ViewController.h"

#include "Textures/Textures.h"

void GameInterfaceScreen::constructScreen() {
    using namespace game_engine::primitives;

    m_gamePointsConnection = GamePointsController::instance()->fireGamePointsChanged.connect([this](int gamePoints) {
        m_pointsText->setText(std::to_string(gamePoints));
    });

    m_cashValueConnection = CashValueController::instance()->fireCashValueChanged.connect([this](int cashValue) {
        m_currencyText->setText(std::to_string(cashValue));
    });

    const auto cashValue = CashValueController::instance()->cashValue();
    const auto gamePoints = GamePointsController::instance()->points();
    const auto viewPos = ViewController::instance()->getViewPos();

    m_currencySprite = std::make_shared<Sprite>(TextureHolder::instance()->coin_texture());
    m_currencySprite->setScale({ 1.5f, 1.5f });
    m_currencySprite->setPosition({ viewPos.x + CASH_FROM_LEFT_OFFSET, viewPos.y + CASH_FROM_TOP_OFFSET });
    m_currencyText = std::make_shared<Text>(game_engine::FONT, std::to_string(cashValue), CASH_TEXT_SIZE);
    m_currencyText->setFillColor(colors::White);
    m_currencyText->setPosition({ viewPos.x + CASH_FROM_LEFT_OFFSET + m_currencySprite->getTextureRect().getSize().x + CASH_TEXT_MARGIN, viewPos.y + CASH_FROM_TOP_OFFSET - CASH_TEXT_SIZE / 2 });

    m_pointsText = std::make_shared<Text>(game_engine::FONT, std::to_string(gamePoints), GAME_POINTS_TEXT_SIZE);
    m_pointsText->setFillColor(colors::White);
    m_pointsText->setPosition({ viewPos.x + GAME_POINTS_FROM_LEFT_OFFSET, viewPos.y + GAME_POINTS_FROM_TOP_OFFSET });

    m_levelTimerText = std::make_shared<Text>(game_engine::FONT, std::to_string(m_levelTimer->remainingTime()), LEVEL_TIMER_TEXT_SIZE);
    m_levelTimerText->setFillColor(colors::White);
    m_levelTimerText->setPosition({ viewPos.x + GAME_POINTS_FROM_LEFT_OFFSET, viewPos.y + GAME_POINTS_FROM_TOP_OFFSET });

    m_primitivesDrawableObjects.push_back(std::make_pair(m_currencySprite, false));
    m_primitivesDrawableObjects.push_back(std::make_pair(m_currencyText, false));
    m_primitivesDrawableObjects.push_back(std::make_pair(m_pointsText, false));
    m_primitivesDrawableObjects.push_back(std::make_pair(m_levelTimerText, false));
}

void GameInterfaceScreen::Update(float time) {
    const auto viewPos = ViewController::instance()->getViewPos();
    m_currencySprite->setPosition({ viewPos.x + CASH_FROM_LEFT_OFFSET, viewPos.y + CASH_FROM_TOP_OFFSET });
    m_currencyText->setPosition({ viewPos.x + CASH_FROM_LEFT_OFFSET + m_currencySprite->getTextureRect().getSize().x + CASH_TEXT_MARGIN, viewPos.y + CASH_FROM_TOP_OFFSET - CASH_TEXT_SIZE / 2 });
    m_pointsText->setPosition({ viewPos.x + GAME_POINTS_FROM_LEFT_OFFSET, viewPos.y + GAME_POINTS_FROM_TOP_OFFSET });

    auto a = std::to_string(m_levelTimer->remainingTime());
    m_levelTimerText->setText(std::to_string(m_levelTimer->remainingTime()));
    m_levelTimerText->setPosition({ viewPos.x + VIEW_WIDTH / 2 - m_levelTimerText->getLocalBounds().getSize().x / 2, viewPos.y + LEVEL_TIMER_FROM_TOP_OFFSET });
}
