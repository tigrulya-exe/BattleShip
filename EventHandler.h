#pragma once

class EventHandler
{
public:
	virtual void execute() = 0;
};

class MenuEventHandler : public EventHandler {
public:
	void execute() override;
};

