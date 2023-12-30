#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    sf::Texture player;

    static void setTextures() {
        player.loadFromFile("./Assets/player/character_idle_1.png");
    }
}