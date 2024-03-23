#include "wisco/MatchController.hpp"

namespace wisco
{
MatchController::MatchController(std::unique_ptr<IMenu>& menu, const std::shared_ptr<io::ITouchScreen>& touch_screen, const std::shared_ptr<rtos::IDelayer>& delayer, const std::shared_ptr<user::IController>& controller) : 
	m_menu{std::move(menu)}, m_touch_screen{touch_screen}, m_delayer{delayer}, m_controller{controller}
{

}

void MatchController::initialize()
{
	if (m_menu)
	{
		m_menu->display();
		while (!m_menu->isStarted())
			m_delayer->delay(MENU_DELAY);
	}

	SystemConfiguration system_configuration{m_menu->getSystemConfiguration()};
	autonomous_manager.setAutonomous(system_configuration.autonomous);
	opcontrol_manager.setProfile(system_configuration.profile);
	robot = system_configuration.configuration->buildRobot();
	if (robot)
	{
		robot->initialize();
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
		opcontrol_manager.runOpcontrol(m_controller, robot, m_touch_screen, m_delayer);
}
} // namespace wisco