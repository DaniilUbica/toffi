#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    std::map<State, sf::Texture> player_textures;

    static void setTextures() {
        player_textures[State::IDLE].loadFromFile("C:/Users/acvel/source/repos/toffi/toffi/Assets/player/idle.png");
        player_textures[State::RUN].loadFromFile("C:/Users/acvel/source/repos/toffi/toffi/Assets/player/run.png");
    }
}