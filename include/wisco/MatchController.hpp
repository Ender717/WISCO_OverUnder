#ifndef WISCO_MATCH_CONTROLLER_HPP
#define WISCO_MATCH_CONTROLLER_HPP

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