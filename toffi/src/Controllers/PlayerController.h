#pragma once

class Player;

class PlayerController {
public:
    static bool controller_created;

    PlayerController();
    void controllPlayer(Player* player, float time);
};