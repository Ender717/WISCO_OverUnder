#ifndef WISCO_MATCH_CONTROLLER_HPP
#define WISCO_MATCH_CONTROLLER_HPP

#include "rtos/IDelayer.hpp"

#include "AutonomousManager.hpp"
#include "OpcontrolManager.hpp"
#include "IMenu.hpp"
#include "control/ControlSystem.hpp"
#include "user/IController.hpp"
#include "robot/Robot.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Handles the field controller inputs during a match
 * @author Nathan Sandvig
 *
 */
class MatchController
{
private:
	/**
	 * @brief The number of milliseconds to wait to check the menu
	 *
	 */
	static constexpr uint32_t MENU_DELAY{10};

	/**
	 * @brief The menu system
	 * 
	 */
	std::unique_ptr<IMenu> m_menu{};

	/**
	 * @brief The rtos clock
	 * 
	 */
	std::shared_ptr<rtos::IClock> m_clock{};

	/**
	 * @brief The rtos delayer
	 * 
	 */
	std::unique_ptr<rtos::IDelayer> m_delayer{};

	/**
	 * @brief The autonomous management object
	 *
	 */
	AutonomousManager autonomous_manager{m_clock, m_delayer};

	/**
	 * @brief The opcontrol management object
	 * 
	 */
	OPControlManager opcontrol_manager{m_clock, m_delayer};
	
	/**
	 * @brief The control system
	 * 
	 */
	std::shared_ptr<control::ControlSystem> control_system{};

	/**
	 * @brief The user input controller
	 * 
	 */
	std::shared_ptr<user::IController> controller{};

	/**
	 * @brief The robot being controlled
	 *
	 */
	std::shared_ptr<robot::Robot> robot{};

public:
	/**
	 * @brief Construct a new Match Controller object
	 * 
	 * @param menu The menu to use in the match controller
	 * @param clock The rtos clock to use in the match controller
	 * @param delayer The rtos delayer to use in the match controller
	 */
	MatchController(std::unique_ptr<IMenu>& menu, const std::shared_ptr<rtos::IClock>& clock, std::unique_ptr<rtos::IDelayer>& delayer);

	/**
	 * @brief Runs the robot initialization code
	 *
	 */
	void initialize(bool fast_init);

	/**
	 * @brief Runs the robot disablement code
	 *
	 */
	void disabled();

	/**
	 * @brief Runs the robot competition initialization code
	 *
	 */
	void competitionInitialize();

	/**
	 * @brief Runs the robot autonomous code
	 *
	 */
	void autonomous();

	/**
	 * @brief Runs the robot operator control code
	 *
	 */
	void operatorControl();
};
} // namespace wisco
#endif