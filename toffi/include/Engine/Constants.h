#pragma once

constexpr float WINDOW_HEIGHT = 720.0;
constexpr float WINDOW_WIDTH  = 1280.0;

constexpr float SPRITE_SIZE = 64.0;

constexpr float WORLD_HEIGHT = WINDOW_HEIGHT - SPRITE_SIZE;
constexpr float WORLD_WIDTH  = WINDOW_WIDTH - SPRITE_SIZE;

constexpr float PLAYER_SPEED   = 0.1;
constexpr float PLAYER_START_X = WINDOW_WIDTH / 2.0 - SPRITE_SIZE;
constexpr float PLAYER_START_Y = WINDOW_HEIGHT / 2.0 - SPRITE_SIZE;

constexpr float ANIMATION_SPEED = 0.002;