#include <SFML/Graphics.hpp>

#include "include/Engine/Constants.h"
#include "include/Player.h"
#include "include/Textures.h"

constexpr float PLAYER_START_X = WINDOW_WIDTH / 2.0 - SPRITE_SIZE;
constexpr float PLAYER_START_Y = WINDOW_HEIGHT / 2.0 - SPRITE_SIZE;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Toffi Adventure");

	textures::setTextures();

	Player* player = new Player(textures::player_textures, sf::Vector2f(PLAYER_START_X, PLAYER_START_Y));

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

		window.clear(sf::Color::White);
		window.draw(player->getSprite());
		window.display();
	}

	delete player;
	return 0;
}