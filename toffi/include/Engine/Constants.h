#pragma once

constexpr float WINDOW_HEIGHT = 720.0;
constexpr float WINDOW_WIDTH  = 1280.0;

constexpr float VIEW_HEIGHT = 720.0;
constexpr float VIEW_WIDTH  = 1280.0;

constexpr float SPRITE_SIZE = 64.0;

constexpr float WORLD_HEIGHT = 1080; // this should be bigger then 'VIEW_HEIGHT'
constexpr float WORLD_WIDTH  = 1536; // this should be bigger then 'VIEW_WIDTH'

constexpr float PLAYER_SPEED   = 0.2;
constexpr float PLAYER_START_X = WORLD_WIDTH / 2.0 - SPRITE_SIZE;
constexpr float PLAYER_START_Y = WORLD_HEIGHT / 2.0 - SPRITE_SIZE;

constexpr float ANIMATION_SPEED = 0.002;