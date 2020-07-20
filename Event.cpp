#include "Event.h"
#include "GameView.h"

CloseEvent_::CloseEvent_(sf::Event& event_in) : Event_(event_in) {}

void CloseEvent_::handleEvent_(SfmlView& view){
	view.getWindow().close();
}

Event_::Event_(sf::Event& event_in) : _event(event_in) {}

sf::Event & Event_::getEvent_()
{
	return _event;
}

