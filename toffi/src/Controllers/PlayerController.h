#pragma once

#include <memory>

class Player;

class PlayerController {
public:
    static bool controller_created;

    PlayerController(Player* player);
    void controllPlayer( float time);

private:
    Player* m_player;
};
