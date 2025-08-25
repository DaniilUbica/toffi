#include "Engine/World.h"
#include "Engine/Constants.h"

World* World::m_world = nullptr;

World::~World() {
    m_world = nullptr;
}

World* World::getWorld() {
    if (!m_world) {
        m_world = new World();
    }

    return m_world;
}

void World::initWorld(const sf::Texture& background, const sf::Texture& border) {
    m_background_texture = background;
    m_border_texture = border;

    int tiles_amount_width = static_cast<int>(WORLD_WIDTH / SPRITE_SIZE) + 1;
    int tiles_amount_height = static_cast<int>(WORLD_HEIGHT / SPRITE_SIZE) + 1;

    for (int i = 0; i < tiles_amount_width; i++) {
        sf::Sprite tile_sprite(m_border_texture);
        tile_sprite.setPosition({ i * SPRITE_SIZE, 0.0 });
        m_border_sprites.push_back(tile_sprite);
    }
    for (int i = 0; i < tiles_amount_width; i++) {
        sf::Sprite tile_sprite(m_border_texture);
        tile_sprite.setPosition({ i * SPRITE_SIZE, WORLD_HEIGHT });
        m_border_sprites.push_back(tile_sprite);
    }
    for (int i = 0; i < tiles_amount_height; i++) {
        sf::Sprite tile_sprite(m_border_texture);
        tile_sprite.setPosition({ 0.0, i * SPRITE_SIZE });
        m_border_sprites.push_back(tile_sprite);
    }
    for (int i = 0; i < tiles_amount_height; i++) {
        sf::Sprite tile_sprite(m_border_texture);
        tile_sprite.setPosition({ WORLD_WIDTH, i * SPRITE_SIZE });
        m_border_sprites.push_back(tile_sprite);
    }

    m_background_sprite = std::make_shared<sf::Sprite>(m_background_texture);
}

std::vector<sf::Sprite> World::getBorderSprites() const {
    return m_border_sprites;
}

std::shared_ptr<sf::Sprite> World::getBackgroundSprite() const {
    return m_background_sprite;
}

size_t World::getBorderVecSize() const {
    return m_border_sprites.size();
}
