#ifndef WISCO_MATCH_CONTROLLER_HPP
#define WISCO_MATCH_CONTROLLER_HPP

#include "AutonomousManager.hpp"
#include "IMenu.hpp"
#include "hal/rtos/delay.hpp"

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
	 * @brief The autonomous management object
	 *
	 */
	static AutonomousManager autonomous_manager;

	/**
	 * @brief The robot being controlled
	 *
	 */
	static std::shared_ptr<robot::Robot> robot;

public:
	/**
	 * @brief Runs the robot initialization code
	 *
	 */
	static void initialize();

	/**
	 * @brief Runs the robot disablement code
	 *
	 */
	static void disabled();

	/**
	 * @brief Runs the robot competition initialization code
	 *
	 */
	static void competitionInitialize();

	/**
	 * @brief Runs the robot autonomous code
	 *
	 */
	static void autonomous();

	/**
	 * @brief Runs the robot operator control code
	 *
	 */
	static void operatorControl();
};
} // namespace wisco
#endif