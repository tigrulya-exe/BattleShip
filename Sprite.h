#pragma once
#include <SFML/Graphics.hpp>

class Sprite_
{
	sf::Sprite _sf_sprite;
	sf::Texture _sf_texture;
public:
	Sprite_() = default;
	Sprite_(std::string);
	void setTexture(std::string);
	void setTexture(sf::Texture&);
	sf::Sprite& getSfSprite();
};

