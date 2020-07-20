#include "EventHandlerCreator.h"

namespace {
	bool setEventRegister() {
		EventFactory& factory = EventFactory::getAccess();
		factory.registerEvent<CloseEvent_>(sf::Event::Closed);
		return true;
	}

	bool tmp = setEventRegister();
};

void EventFactory::initEventRegister(const sf::Event::EventType event_type, std::shared_ptr<IEventCreator> creator){
	_events[event_type] = creator;
}

Event_* EventFactory::getEvent_(sf::Event& event_in)
{
	return _events[event_in.type]->createEvent(event_in);
}

EventFactory& EventFactory::getAccess()
{
	static EventFactory factory;
	return factory;
}
