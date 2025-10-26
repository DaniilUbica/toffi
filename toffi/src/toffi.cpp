#include "Constants.h"

#include "Engine/World.h"
#include "Engine/TimersHolder.hpp"
#include "Engine/GameStateMachine.h"

#include "GameScreens/GameOverScreen.h"

#include "Primitives/Clock.hpp"

#include "Enemies/EnemiesManager.h"
#include "GameManager.h"

int main() {
    srand(time(NULL));

    game_engine::primitives::Clock clock;

    game_engine::primitives::RenderWindow window({ WINDOW_WIDTH, WINDOW_HEIGHT }, "Toffi Adventure");

    GameManager game_manager(window);
    game_manager.initGame();

    game_manager.gameStateMachine()->fireGameResumed.connect([clock]() mutable {
        clock.reset();
    });

    while (window.isOpen()) {
        float time = clock.getElapsedTime();
        time /= 300;
        clock.restart();

        game_manager.handleEvent(window.pollEvent());

        game_manager.Update(time);

        window.clear(game_engine::primitives::colors::White);

        game_manager.drawGameObjects();

        window.display();
    }

    game_manager.deinitGame();
    return 0;
}
