#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
    std::map<State, sf::Texture> player_textures;

    sf::Texture lvl1_border_texture;
    sf::Texture flying_eye_texture;

    static void setTextures() {
        player_textures[State::IDLE].loadFromFile("./Assets/player/idle.png");
        player_textures[State::RUN].loadFromFile("./Assets/player/run.png");

        lvl1_border_texture.loadFromFile("./Assets/level_1/border.png");

        flying_eye_texture.loadFromFile("./Assets/enemies/eye_flight.png");
    }
}