#include <SFML/Graphics.hpp>

#include "include/Engine/Constants.h"
#include "include/Engine/World.h"
#include "include/Engine/ViewController.h"
#include "include/Player.h"
#include "include/Textures.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Toffi Adventure");

	textures::setTextures();

	Player* player = new Player(textures::player_textures, sf::Vector2f(PLAYER_START_X, PLAYER_START_Y));

	World* world = World::getWorld();
	world->initWorld(textures::lvl1_border_texture);

	ViewController view_controller(player);

	sf::Clock clock;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 300;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		player->Update(time);
		view_controller.Update(time, window);

		window.clear(sf::Color::White);
		for (int i = 0; i < world->getBorderVecSize(); i++) {
			window.draw(world->getBorderSprites()[i]);
		}
		window.draw(player->getSprite());
		
		window.display();
	}

	delete player;
	return 0;
}