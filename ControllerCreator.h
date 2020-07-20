#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "GameModel.h"


class IControllerCreator {
public:
	virtual Controller* createController(GameModel&) = 0;
};

//RENAME
template <class T>
class ControllerCreator : public IControllerCreator {
public:
	T* createController(GameModel& model_in) override { return new T(model_in); }
};

class ControllerFactory {
	std::map<enum gameStage, std::shared_ptr<IControllerCreator>> _controllers;
	void initControllerRegister(enum gameStage, std::shared_ptr<IControllerCreator>);
	ControllerFactory() = default;
public:
	template <class T>
	void registerController(enum gameStage curr_stage) {
		auto controller_creator = std::make_shared<ControllerCreator<T>>();
		ControllerFactory::getAccess().initControllerRegister(curr_stage, controller_creator);
	}
	Controller* getController(GameModel&);
	static ControllerFactory& getAccess();
};