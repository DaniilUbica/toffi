#pragma once

#include "cpplib/singletone.hpp"

#include <nod/nod.hpp>

class GamePointsController : public game_engine::cpplib::singletone_from_this<GamePointsController> {
public:
    void addPoints(int count);
    int points() const { return m_points; };

    nod::signal<void(int)> fireGamePointsChanged;

private:
    int m_points = 0;
};
