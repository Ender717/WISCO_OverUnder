#ifndef WISCO_AUTONS_BLUE_MATCH_AUTON_HPP
#define WISCO_AUTONS_BLUE_MATCH_AUTON_HPP

#include "wisco/IAutonomous.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for autonomous routines
 * @author Nathan Sandvig
 * 
 */
namespace autons
{

/**
 * @brief The auton for the blue robot in matches
 * @author Nathan Sandvig
 * 
 */
class BlueMatchAuton : public IAutonomous
{
private:
    /**
     * @brief The name of the autonomous
     * 
     */
    static constexpr char AUTONOMOUS_NAME[]{"B_MATCH"};

	/**
	 * @brief The name of the boomerang control
	 * 
	 */
	static constexpr char BOOMERANG_CONTROL_NAME[]{"BOOMERANG"};

	/**
	 * @brief The name of the boomerang go to position command
	 * 
	 */
	static constexpr char BOOMERANG_GO_TO_POSITION_COMMAND_NAME[]{"GO TO POSITION"};

	/**
	 * @brief The name of the boomerang pause command
	 * 
	 */
	static constexpr char BOOMERANG_PAUSE_COMMAND_NAME[]{"PAUSE"};

	/**
	 * @brief The name of the boomerang resume command
	 * 
	 */
	static constexpr char BOOMERANG_RESUME_COMMAND_NAME[]{"RESUME"};

	/**
	 * @brief The name of the boomerang target reached state
	 * 
	 */
	static constexpr char BOOMERANG_TARGET_REACHED_STATE_NAME[]{"TARGET REACHED"};

	/**
	 * @brief Calls the boomerang go to point command
	 * 
	 * @param control_system The control system
	 * @param robot The robot
	 * @param velocity The motion velocity
	 * @param x The target x-coordinate
	 * @param y The target y-coordinate
	 * @param theta The target angle
	 */
	void boomerangGoToPoint(std::shared_ptr<control::ControlSystem> control_system, 
							std::shared_ptr<robot::Robot> robot, 
							double velocity, double x, double y, double theta);

	/**
	 * @brief Pauses the boomerang motion
	 * 
	 * @param control_system The control system
	 */
	void boomerangPause(std::shared_ptr<control::ControlSystem> control_system);

	/**
	 * @brief Resumes the boomerang motion
	 * 
	 * @param control_system The control system
	 */
	void boomerangResume(std::shared_ptr<control::ControlSystem> control_system);

	/**
	 * @brief Checks if the boomerang target has been reached
	 * 
	 * @param control_system The control system
	 * @return true The boomerang target has been reached
	 * @return false The boomerang target has not been reached
	 */
	bool boomerangTargetReached(std::shared_ptr<control::ControlSystem> control_system);

public:
    /**
	 * @brief Get the name of the autonomous
	 *
	 * @return std::string The name of the autonomous
	 */
	std::string getName() override;

	/**
	 * @brief Initialize the autonomous
	 *
	 */
	void initialize(std::shared_ptr<control::ControlSystem> control_system, 
					std::shared_ptr<robot::Robot> robot) override;

	/**
	 * @brief Run the autonomous
	 *
	 */
	void run(std::shared_ptr<control::ControlSystem> control_system, 
			 std::shared_ptr<robot::Robot> robot) override;
};
}
}

#endif