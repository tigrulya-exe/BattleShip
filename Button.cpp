#include "Button.h"

sf::Sprite & Button::getSprite()
{
	return _sprite;
}

ViewEvent& Button::getPressedEvent()
{
	return _pressed_event;
}

void Button::setCurrTexture(sf::Texture * texture_in) {
	_curr_texture = texture_in;
	_sprite.setTexture(*_curr_texture);
}

ButtonState & Button::getState()
{
	return _state;
}

Button::~Button(){
	delete _texture_captured;
	delete _texture_clear;
}

Button::Button(int x, int y, std::string clear_path, std::string captured_path) : _texture_captured(new sf::Texture), _texture_clear(new sf::Texture) {
	_texture_clear->loadFromFile(clear_path);
	_texture_captured->loadFromFile(captured_path);
	_curr_texture = _texture_clear;

	_pressed_event._type = EventType::Nothing;

	setSprite();
	_sprite.setPosition(x, y);

	_state = ButtonState::Free;
}

void Button::setSprite() {
	_sprite.setTexture(*_curr_texture);
}

void Button::setTextureClear() {
	_curr_texture = _texture_clear;
	setSprite();
}

void Button::setTextureCaptured() {
	_curr_texture = _texture_captured;
	setSprite();
}

void Button::setTexture(std::string & path) {
	_curr_texture->loadFromFile(path);
	_sprite.setTexture(*_curr_texture);
}

void Button::setViewEvent(ViewEvent event_in) {
	_pressed_event = event_in;
}


void Cell::setTextures(std::string txt_clear, std::string txt_cartured) {
	_textures[CellState::Arr_Water].loadFromFile(txt_clear);
	_textures[CellState::Arr_Border].loadFromFile(path::BORDER);
	_textures[CellState::Arr_Set].loadFromFile(txt_cartured);
	_textures[CellState::Arr_Placed].loadFromFile(txt_cartured);
	_textures[CellState::Hit].loadFromFile(path::BOAT_HIT);
	_textures[CellState::Miss].loadFromFile(path::WATER_MISS);
	_textures[CellState::Kill].loadFromFile(path::BOAT_KILL);
}

Cell::Cell(int x, int y, std::string txt_clear, std::string txt_cartured) : Button(x, y, txt_clear, txt_cartured) {
	setTextures(txt_clear, txt_cartured);
}

void Cell::setTexture(CellState state_in) {
	setCurrTexture(&_textures[state_in]);
}

void Cell::setPressCoords(int x, int y) {
	ViewEvent& tmp = getPressedEvent();
	tmp.cellPressed.SetCoords(x, y);
}


SmallCell::SmallCell(int x, int y, std::string txt_clear, std::string txt_cartured) : Cell(x, y, txt_clear, txt_cartured) {
	setTextures(txt_clear, txt_cartured);
}
//tmp
void SmallCell::setTexture(CellState state_in)
{
	setCurrTexture(&_textures[state_in]);
}

void SmallCell::setTextures(std::string txt_clear, std::string txt_cartured) {
	_textures[CellState::Arr_Water].loadFromFile(txt_clear);
	_textures[CellState::Arr_Placed].loadFromFile(txt_cartured);

	_textures[CellState::Hit].loadFromFile(path::BOAT_HIT_SMALL);
	_textures[CellState::Miss].loadFromFile(path::WATER_MISS_SMALL);
	_textures[CellState::Kill].loadFromFile(path::BOAT_KILL_SMALL);
}
