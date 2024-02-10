#include "wisco/MatchController.hpp"

namespace wisco
{
MatchController::MatchController(std::unique_ptr<IMenu>& menu) : m_menu{std::move(menu)}
{

}

void MatchController::initialize()
{
	if (m_menu)
	{
		m_menu->display();
		while (!m_menu->isStarted())
			hal::rtos::delay(MENU_DELAY);
	}

	SystemConfiguration system_configuration{m_menu->getSystemConfiguration()};
	autonomous_manager.setAutonomous(system_configuration.autonomous);
	opcontrol_manager.setProfile(system_configuration.profile);
	robot = system_configuration.configuration->buildRobot();
	if (robot)
	{
		autonomous_manager.initializeAutonomous(robot);
		opcontrol_manager.initializeOpcontrol(robot);
	}
}

void MatchController::disabled()
{

}

void MatchController::competitionInitialize()
{

}

void MatchController::autonomous()
{
	if (robot)
		autonomous_manager.runAutonomous(robot);
}

void MatchController::operatorControl()
{
	if (robot)
		opcontrol_manager.runOpcontrol(robot);
}
} // namespace wisco