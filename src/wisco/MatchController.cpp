#include "wisco/MatchController.hpp"

namespace wisco
{
MatchController::MatchController(std::unique_ptr<IMenu>& menu, const std::shared_ptr<rtos::IClock>& clock, std::unique_ptr<rtos::IDelayer>& delayer) : 
	m_menu{std::move(menu)}, m_clock{clock}, m_delayer{std::move(delayer)}, opcontrol_manager{m_clock, m_delayer}
{

}

void MatchController::initialize()
{
	if (m_menu)
	{
		m_menu->display();
		while (m_delayer && !m_menu->isStarted())
			m_delayer->delay(MENU_DELAY);
	}

	SystemConfiguration system_configuration{};
	if (m_menu)
		system_configuration = m_menu->getSystemConfiguration();
	autonomous_manager.setAutonomous(system_configuration.autonomous);
	opcontrol_manager.setProfile(system_configuration.profile);
	controller = system_configuration.configuration->buildController();
	robot = system_configuration.configuration->buildRobot();

	if (robot)
	{
		robot->initialize();
		autonomous_manager.initializeAutonomous(robot);
		if (controller)
		{
			controller->initialize();
			controller->run();
			opcontrol_manager.initializeOpcontrol(controller, robot);
		}
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
	if (controller && robot)
		opcontrol_manager.runOpcontrol(controller, robot);
}
} // namespace wisco