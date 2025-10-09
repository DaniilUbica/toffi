#pragma once

#include <memory>

#include <nod/nod.hpp>

class GamePointsController {
public:
    static std::shared_ptr<GamePointsController> instance();

    void addPoints(int count);
    int points() const { return m_points; };

    nod::signal<void(int)> fireGamePointsChanged;

private:
    GamePointsController() = default;
    GamePointsController(const GamePointsController&) = delete;
    void operator=(const GamePointsController&) = delete;

    inline static std::weak_ptr<GamePointsController> m_instance;

    int m_points = 0;
};
