#include "GameView.h"
#include <iostream>

const int GAMELOGO_DELAY = 1700;

bool SfmlView::isBotAction()
{
	if (_model.getCurrentPlayerType() != playerType::Human && (_curr_stage == gameStage::Arrangement || _curr_stage == gameStage::GameStage)) {
		return true;
	}
	return false;
}

void SfmlView::checkStage(gameStage stage_in){
	if (stage_in != _curr_stage) {
		_curr_stage = stage_in;
		_curr_window_drawer = WindowDrawerFactory::getAccess().getWindowDrawer(stage_in,_curr_sf_window);
	}
}

void SfmlView::renderChanges(){
	if (_model.getClosed()) {
		_curr_sf_window.close();
	}
}

//void SfmlView::setMusic(){
//	_main_theme.openFromFile(musicPath::MENU);
//	_main_theme.setLoop(true);
//	_main_theme.play();
//}

SfmlView::SfmlView(GameModel& model_in) : _curr_stage(gameStage::Menu), _curr_window_drawer(new MenuDrawer{_curr_sf_window}), _model(model_in) {
	_curr_sf_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_LENGTH), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
	_curr_sf_window.setFramerateLimit(FRAMERATE_LIMIT);
	_curr_sf_window.clear(sf::Color::Black);

	sf::Image icon;
	icon.loadFromFile(ICON_PATH);
	_curr_sf_window.setIcon(icon.getSize().x,icon.getSize().y, icon.getPixelsPtr());
	//setMusic();
}

void SfmlView::render(){
	checkStage(_model.getCurrentStage());
	_curr_window_drawer->checkChanges(_model);
	_curr_window_drawer->draw(_model);

	_curr_sf_window.display();
	//_curr_sf_window.clear(sf::Color::White);
}

sf::RenderWindow& SfmlView::getWindow()
{
	return _curr_sf_window;
}

ViewEvent& SfmlView::getViewEvent(sf::Event& sf_event){

	if (isBotAction()) {
		return _model.getCurrentPlayer()->play(_curr_stage, _model.getCurrentPlayerNum());
	}
	return _curr_window_drawer->checkButtons(sf_event);
}

void SfmlView::renderGameLogo()
{
	sf::Sprite backgroung;
	sf::Texture game_logo;
	game_logo.loadFromFile(GAMELOGO_PATH);
	backgroung.setTexture(game_logo);
	_curr_sf_window.draw(backgroung);
	_curr_sf_window.display();

	sf::sleep(sf::milliseconds(GAMELOGO_DELAY));
}

SfmlView::~SfmlView(){
	delete _curr_window_drawer;
}
