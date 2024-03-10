#pragma once

#include <SFML/Graphics.hpp>

class World {
private:
    static World*           m_world;

    sf::Texture             m_border_texture;
    sf::Texture             m_background_texture;
    sf::Sprite              m_background_sprite;
    std::vector<sf::Sprite> m_border_sprites;

    World() = default;
public:
    World(World const& world) = delete;
    void operator=(World const&) = delete;
    ~World();

    static World* getWorld();

    void initWorld(const sf::Texture& background, sf::Texture& border);

    std::vector<sf::Sprite> getBorderSprites() const;
    sf::Sprite getBackgroundSprite() const;
    size_t getBorderVecSize() const;
};