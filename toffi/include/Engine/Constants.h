#pragma once

constexpr float PI = 3.14159265;

constexpr float WINDOW_HEIGHT = 720.0;
constexpr float WINDOW_WIDTH  = 1280.0;

constexpr float VIEW_HEIGHT = 720.0;
constexpr float VIEW_WIDTH  = 1280.0;

constexpr float SPRITE_SIZE = 64.0;

constexpr float WORLD_HEIGHT = 1080; // this should be bigger then 'VIEW_HEIGHT'
constexpr float WORLD_WIDTH  = 1536; // this should be bigger then 'VIEW_WIDTH'

constexpr float PLAYER_SPEED              = 0.12;
constexpr float PLAYER_START_X            = WORLD_WIDTH / 2.0 - SPRITE_SIZE;
constexpr float PLAYER_START_Y            = WORLD_HEIGHT / 2.0 - SPRITE_SIZE;
constexpr float PLAYER_START_ATTACK_SPEED = 1.0;
constexpr float PLAYER_START_ATTACK_RANGE = 200.0;
constexpr float PLAYER_START_HP           = 15.0;

constexpr float ANIMATION_SPEED = 0.002;

constexpr float ENEMY_SPEED               = 0.07;
constexpr float ENEMY_START_HP            = 25.0;
constexpr float ENEMY_ATTACK_COOLDOWN     = 1.5;
constexpr float ENEMY_DAMAGE              = 1.0;
constexpr float ENEMY_RESPAWN_TIMER       = 2.5;
constexpr float ENEMY_MINIMAL_SPAWN_POS_X = 120.0;
constexpr float ENEMY_MINIMAL_SPAWN_POS_Y = 120.0;
constexpr float ENEMY_MAXIMAL_SPAWN_POS_X = WORLD_WIDTH - 120.0;
constexpr float ENEMY_MAXIMAL_SPAWN_POS_Y = WORLD_HEIGHT - 120.0;
constexpr float ENEMY_SPAWN_RANGE         = 100.0;
constexpr float ENEMY_ATTACK_RANGE        = 250.0;
constexpr float ENEMY_BULLET_DAMAGE       = 3.0;

constexpr float BULLET_DEFAULT_SIZE   = 24.0;
constexpr float BULLET_DEFAULT_SPEED  = 0.2;
constexpr float BULLET_DEFAULT_DAMAGE = 20.0;

constexpr float HEAL_DEFAULT_VALUE = 1.0;
constexpr float HEAL_SPAWN_CHANCE  = 20.0;

constexpr float PARTICLE_RADIUS = 2.0;
constexpr float PARTICLE_SPEED  = 5.0;

constexpr int BURSTING_BUBBLE_PARTICLES_COUNT = 100;

constexpr int BULLET_WAVE_BULLETS_SPACING = 15;
constexpr int BULLET_WAVE_SPAWN_CHANCE    = 10;
constexpr float BULLET_WAVE_DAMAGE        = 40;
