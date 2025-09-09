#include "Primitives/Rect/Rect.hpp"
#include "Primitives/Sprite/Sprite.hpp"
#include "Primitives/Texture/Texture.hpp"
#include "Primitives/RenderWindow/RenderWindow.hpp"


int main() {

    auto q = game_engine::primitives::Rect<int>(1, 2, 3, 5);
    auto w = game_engine::primitives::Rect<int>(10, 20, 30, 50);
    auto res = q.intersects(w);

    game_engine::primitives::Texture texture("border.png");
    auto sprite = game_engine::primitives::Sprite(texture);
//    sprite.setPosition({50, 50});

    game_engine::primitives::engineRectToSfRect(q);

    auto window = game_engine::primitives::RenderWindow({200, 200}, "qwe");
    auto ww = sprite.getTextureRect();
    auto e = sprite.getGlobalBounds();

    while (window.isOpen()) {
        window.clear(255, 255, 255);

        window.draw(sprite);

        window.display();
    }

	return 0;
}
