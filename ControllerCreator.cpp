#include "ControllerCreator.h"

namespace {
	bool setControllerRegister() {
		ControllerFactory& factory = ControllerFactory::getAccess();
		factory.registerController<MenuController>(gameStage::Menu);
		factory.registerController<OptionsController>(gameStage::Options);
		factory.registerController<ArrangementController>(gameStage::Arrangement);
		factory.registerController<GameController>(gameStage::GameStage);
		factory.registerController <FinishController>(gameStage::Finish);
		factory.registerController <StatsController>(gameStage::Stats);
		factory.registerController <HelpController>(gameStage::Help);
		return true;
	}

	bool tmp = setControllerRegister();
};

void ControllerFactory::initControllerRegister(gameStage curr_stage, std::shared_ptr<IControllerCreator> controller_creator) {
	_controllers[curr_stage] = controller_creator;
}

Controller* ControllerFactory::getController(GameModel& model_in)
{
	return _controllers[model_in.getCurrentStage()]->createController(model_in);
}

ControllerFactory & ControllerFactory::getAccess()
{
	static ControllerFactory factory;
	return factory;
}
