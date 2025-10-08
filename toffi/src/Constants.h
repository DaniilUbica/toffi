#pragma once

#include "Engine/Constants.h"

constexpr unsigned int WINDOW_HEIGHT = 720;
constexpr unsigned int WINDOW_WIDTH  = 1280;

constexpr float VIEW_HEIGHT = 720.0;
constexpr float VIEW_WIDTH  = 1280.0;

constexpr float PLAYER_SPEED              = 0.12;
constexpr float PLAYER_START_X            = game_engine::WORLD_WIDTH / 2.0 - game_engine::SPRITE_SIZE;
constexpr float PLAYER_START_Y            = game_engine::WORLD_HEIGHT / 2.0 - game_engine::SPRITE_SIZE;
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
constexpr float ENEMY_MAXIMAL_SPAWN_POS_X = game_engine::WORLD_WIDTH - 120.0;
constexpr float ENEMY_MAXIMAL_SPAWN_POS_Y = game_engine::WORLD_HEIGHT - 120.0;
constexpr float ENEMY_SPAWN_RANGE         = 100.0;
constexpr float ENEMY_ATTACK_RANGE        = 250.0;
constexpr float ENEMY_BULLET_DAMAGE       = 3.0;

constexpr float BULLET_DEFAULT_SIZE   = 24.0;
constexpr float BULLET_DEFAULT_SPEED  = 0.2;
constexpr float BULLET_DEFAULT_DAMAGE = 20.0;

constexpr float MELEE_WEAPON_DEFAULT_DAMAGE = 40.0;

constexpr float HEAL_DEFAULT_VALUE = 1.0;
constexpr float HEAL_SPAWN_CHANCE  = 20.0;

constexpr int BULLET_WAVE_BULLETS_SPACING = 15;
constexpr int BULLET_WAVE_SPAWN_CHANCE    = 10;
constexpr float BULLET_WAVE_DAMAGE        = 40.0;

constexpr int CURRENCY_SPAWN_CHANCE    = 100;
constexpr int CURRENCY_SPAWN_MIN_VALUE = 1;
constexpr int CURRENCY_SPAWN_MAX_VALUE = 5;

const std::string GAME_OVER_TEXT                   = "GAME OVER";
const std::string GAME_OVER_RESTART_TEXT           = "Press 'R' to restart";
constexpr unsigned int GAME_OVER_TEXT_SIZE         = 72;
constexpr unsigned int GAME_OVER_RESTART_TEXT_SIZE = 56;
constexpr float GAME_OVER_TEXT_Y_OFFSET            = 100;
constexpr float GAME_OVER_RESTART_TEXT_Y_OFFSET    = 50;

constexpr unsigned int GAME_POINTS_TEXT_SIZE        = 56;
constexpr unsigned int GAME_POINTS_FROM_TOP_OFFSET  = 46;
constexpr unsigned int GAME_POINTS_FROM_LEFT_OFFSET = 72;

constexpr int MELEE_ENEMY_KILL_POINTS = 20;
constexpr int RANGE_ENEMY_KILL_POINTS = 10;

const std::string DB_GAME_DATA_DB_NAME       = "game_data";
const std::string DB_GAME_DATA_RELATION_NAME = "game_data";

const std::pair<std::string, std::string> DB_GAME_POINTS_RECORD_FIELD_DATA = { "best_score", "INT" };
