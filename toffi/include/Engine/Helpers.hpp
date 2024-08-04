#pragma once

#include "SFML/Graphics.hpp"

sf::Color calculateAverageTextureColor(const sf::Texture& texture) {
	sf::Vector2u size = texture.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;

	sf::Image image = texture.copyToImage();

	float redSum = 0;
	float greenSum = 0;
	float blueSum = 0;
	float alphaSum = 0;

	int pixelCount = width * height;

	for (unsigned int x = 0; x < width; ++x) {
		for (unsigned int y = 0; y < height; ++y) {
			sf::Color color = image.getPixel(x, y);
			if (color.a == 0) {
				pixelCount--;
				continue;
			}

			redSum += color.r;
			greenSum += color.g;
			blueSum += color.b;
			alphaSum += color.a;
		}
	}

	float avgRed = redSum / pixelCount;
	float avgGreen = greenSum / pixelCount;
	float avgBlue = blueSum / pixelCount;
	float avgAlpha = alphaSum / pixelCount;

	return sf::Color(avgRed, avgGreen, avgBlue, avgAlpha);
}
