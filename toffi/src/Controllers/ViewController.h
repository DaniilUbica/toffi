#pragma once

#include "cpplib/singletone.hpp"

#include "Primitives/RenderWindow/RenderWindow.hpp"
#include "Primitives/View/View.hpp"

class Player;

class ViewController : public game_engine::cpplib::singletone_from_this<ViewController> {
    friend class singletone_from_this<ViewController>;

private:
    std::shared_ptr<Player> m_player;
    std::unique_ptr<game_engine::primitives::View> m_view;

    inline static std::weak_ptr<ViewController> s_instance;

    ViewController();
public:

    void Update(float time, game_engine::primitives::RenderWindow& window);

    [[nodiscard]] game_engine::primitives::Vector2f getViewPos() const { return m_view->getViewRect().getPosition(); };
    [[nodiscard]] game_engine::primitives::Vector2f getViewSize() const { return m_view->getViewRect().getSize(); };

    void setPlayer(std::shared_ptr<Player> player) { m_player = player; };
};

