#include "wisco/MatchController.hpp"
#include "hal/rtos/delay.hpp"

namespace wisco
{

AutonomousManager MatchController::autonomous_manager{};
std::shared_ptr<robot::Robot> MatchController::robot{};

void MatchController::initialize()
{
	std::unique_ptr<IMenu> menu{};

	menu->display();
	while (!menu->isStarted())
		hal::rtos::delay(MENU_DELAY);

	SystemConfiguration system_configuration{menu->getSystemConfiguration()};
	autonomous_manager.setAutonomous(system_configuration.autonomous);
	robot = system_configuration.configuration->buildRobot();

	autonomous_manager.initializeAutonomous(robot);
}

void MatchController::disabled()
{

}

void MatchController::competitionInitialize()
{

}

void MatchController::autonomous()
{
	autonomous_manager.runAutonomous(robot);
}

void MatchController::operatorControl()
{

}
} // namespace wisco