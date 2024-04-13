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
	control_system = system_configuration.configuration->buildControlSystem();
	controller = system_configuration.configuration->buildController();
	robot = system_configuration.configuration->buildRobot();

	if (robot)
		robot->initialize();
	if (control_system)
		control_system->initialize();
	if (controller)
	{
		controller->initialize();
		controller->run();
	}
	
	autonomous_manager.initializeAutonomous(control_system, robot);
	opcontrol_manager.initializeOpcontrol(control_system, controller, robot);
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
		autonomous_manager.runAutonomous(control_system, robot);
}

void MatchController::operatorControl()
{
	if (controller && robot)
		opcontrol_manager.runOpcontrol(control_system, controller, robot);
}
} // namespace wisco