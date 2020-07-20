#include "Sprite.h"

Sprite_::Sprite_(std::string texture_name){
	_sf_texture.loadFromFile(texture_name);
	_sf_sprite.setTexture(_sf_texture);
}

void Sprite_::setTexture(std::string texture_name){
	_sf_texture.loadFromFile(texture_name);
	_sf_sprite.setTexture(_sf_texture);
}

void Sprite_::setTexture(sf::Texture & texture_in){
	_sf_texture = texture_in;
	_sf_sprite.setTexture(texture_in);
}

sf::Sprite & Sprite_::getSfSprite()
{
	return _sf_sprite;
}
