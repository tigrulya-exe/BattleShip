#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Sprite.h"
#include "Field.h"
#include "ViewEvent.h"

namespace {
	namespace path {
		const char* BORDER = "Textures/Field/border.png";
		const char* BOAT_HIT = "Textures/Field/boat_hit.png";
		const char* WATER_MISS = "Textures/Field/water_miss.png";
		const char* BOAT_KILL = "Textures/Field/boat_kill.png";

		const char* BOAT_HIT_SMALL = "Textures/Field/boat_hit_small.png";
		const char* WATER_MISS_SMALL = "Textures/Field/water_miss_small.png";
		const char* BOAT_KILL_SMALL = "Textures/Field/boat_kill_small.png";
	}
}

enum ButtonState {
	Free,
	Pressed
};

class Button {
private:
	sf::Sprite _sprite;
	sf::Texture* _curr_texture;
	sf::Texture* _texture_captured;
	sf::Texture* _texture_clear;

	ViewEvent _pressed_event;
	ButtonState _state;

public:
	Button(int, int, std::string, std::string);
	void setSprite();
	void setTextureClear();
	void setTextureCaptured();
	void setTexture(std::string&);

	void setViewEvent(ViewEvent);
	sf::Sprite& getSprite();

	ViewEvent& getPressedEvent();
	void setCurrTexture(sf::Texture*);
	ButtonState& getState();
	virtual ~Button();
};

class Cell : public Button {
public:
	Cell(int, int, std::string, std::string);
	virtual void setTexture(CellState);
	void setPressCoords(int, int);
private:
	std::map <CellState, sf::Texture> _textures;
	void setTextures(std::string, std::string);
};

class SmallCell : public Cell {
public:
	SmallCell(int, int, std::string, std::string);
	void setTexture(CellState) override;
private:
	std::map <CellState, sf::Texture> _textures;
	void setTextures(std::string, std::string);
};