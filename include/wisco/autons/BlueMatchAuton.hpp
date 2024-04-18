#ifndef WISCO_AUTONS_BLUE_MATCH_AUTON_HPP
#define WISCO_AUTONS_BLUE_MATCH_AUTON_HPP

#include <cmath>

#include "wisco/control/motion/ETurnDirection.hpp"
#include "wisco/control/path/QuinticBezierSpline.hpp"
#include "wisco/robot/subsystems/drive/Velocity.hpp"
#include "wisco/robot/subsystems/position/Position.hpp"

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
	 * @brief The name of the path following control
	 * 
	 */
	static constexpr char PATH_FOLLOWING_CONTROL_NAME[]{"PATH FOLLOWING"};

	/**
	 * @brief The name of the odometry subsystem
	 * 
	 */
	static constexpr char ODOMETRY_SUBSYSTEM_NAME[]{"POSITION TRACKER"};

	/**
	 * @brief The name of the boomerang go to position command
	 * 
	 */
	static constexpr char BOOMERANG_GO_TO_POSITION_COMMAND_NAME[]{"GO TO POSITION"};

	/**
	 * @brief The name of the path following follow path command
	 * 
	 */
	static constexpr char PATH_FOLLOWING_FOLLOW_PATH_COMMAND_NAME[]{"FOLLOW PATH"};

	/**
	 * @brief The name of the path following set velocity command
	 * 
	 */
	static constexpr char PATH_FOLLOWING_SET_VELOCITY_COMMAND_NAME[]{"SET VELOCITY"};

	/**
	 * @brief The name of the odometry set position command
	 * 
	 */
	static constexpr char ODOMETRY_SET_POSITION_COMMAND_NAME[]{"SET POSITION"};

	/**
	 * @brief The name of the boomerang target reached state
	 * 
	 */
	static constexpr char BOOMERANG_TARGET_REACHED_STATE_NAME[]{"TARGET REACHED"};

	/**
	 * @brief The name of the path following target reached state
	 * 
	 */
	static constexpr char PATH_FOLLOWING_TARGET_REACHED_STATE_NAME[]{"TARGET REACHED"};

	/**
	 * @brief The name of the odometry get position state
	 * 
	 */
	static constexpr char ODOMETRY_GET_POSITION_STATE_NAME[]{"GET POSITION"};

    /**
     * @brief The name of the motion control
     * 
     */
    static constexpr char MOTION_CONTROL_NAME[]{"MOTION"};

    /**
     * @brief The name of the motion turn to angle command
     * 
     */
    static constexpr char MOTION_TURN_TO_ANGLE_COMMAND_NAME[]{"TURN TO ANGLE"};

    /**
     * @brief The name of the motion turn to point command
     * 
     */
    static constexpr char MOTION_TURN_TO_POINT_COMMAND_NAME[]{"TURN TO POINT"};

    /**
     * @brief The name of the motion turn target reached state
     * 
     */
    static constexpr char MOTION_TURN_TARGET_REACHED_STATE_NAME[]{"TURN TARGET REACHED"};

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
	 * @brief Checks if the boomerang target has been reached
	 * 
	 * @param control_system The control system
	 * @return true The boomerang target has been reached
	 * @return false The boomerang target has not been reached
	 */
	bool boomerangTargetReached(std::shared_ptr<control::ControlSystem> control_system);

	/**
	 * @brief Sets the odometry position
	 * 
	 * @param robot The robot
	 * @param x The x-coordinate
	 * @param y The y-coordinate
	 * @param theta The angle
	 */
	void odometrySetPosition(std::shared_ptr<robot::Robot> robot, 
							 double x, double y, double theta);

	/**
	 * @brief Gets the odometry position
	 * 
	 * @param robot The robot
	 * @return robot::subsystems::position::Position The odometry position
	 */
	robot::subsystems::position::Position odometryGetPosition(std::shared_ptr<robot::Robot> robot);

	/**
	 * @brief Calls the motion turn to angle command
	 * 
	 * @param control_system The control system
	 * @param robot The robot
	 * @param velocity The turn velocity
	 * @param theta The target angle
	 * @param reversed Whether or not to turn to face away from the point
	 * @param direction The turn direction (default auto)
	 */
	void motionTurnToAngle(std::shared_ptr<control::ControlSystem> control_system, 
							std::shared_ptr<robot::Robot> robot, 
							double velocity, double theta, bool reversed = false,
							control::motion::ETurnDirection direction = control::motion::ETurnDirection::AUTO);

	/**
	 * @brief Calls the motion turn to point command
	 * 
	 * @param control_system The control system
	 * @param robot The robot
	 * @param velocity The turn velocity
	 * @param x The target x-coordinate
	 * @param y The target y-coordinate
	 * @param reversed Whether or not to turn to face away from the point
	 * @param direction The turn direction (default auto)
	 */
	void motionTurnToPoint(std::shared_ptr<control::ControlSystem> control_system, 
							std::shared_ptr<robot::Robot> robot, 
							double velocity, double x, double y, bool reversed = false,
							control::motion::ETurnDirection direction = control::motion::ETurnDirection::AUTO);

	/**
	 * @brief Checks if the motion turn target has been reached
	 * 
	 * @param control_system The control system
	 * @return true The motion turn target has been reached
	 * @return false The motion turn target has not been reached
	 */
	bool motionTurnTargetReached(std::shared_ptr<control::ControlSystem> control_system);

	/**
	 * @brief Calls the path following follow path command
	 * 
	 * @param control_system The control system
	 * @param robot The robot
	 * @param path The path to follow
	 * @param velocity The path following velocity
	 */
	void pathFollowingFollowPath(std::shared_ptr<control::ControlSystem> control_system, 
								 std::shared_ptr<robot::Robot> robot, 
								 std::vector<control::path::Point> path,
								 double velocity);

	/**
	 * @brief Sets the velocity of the pure pursuit system
	 * 
	 * @param control_system The control system
	 * @param velocity The path following velocity
	 */
	void pathFollowingSetVelocity(std::shared_ptr<control::ControlSystem> control_system,
								  double velocity);

	/**
	 * @brief Checks if the path following target has been reached
	 * 
	 * @param control_system The control system
	 * @return true The path following target has been reached
	 * @return false The path following target has not been reached
	 */
	bool pathFollowingTargetReached(std::shared_ptr<control::ControlSystem> control_system);

	std::vector<control::path::Point> test_path{};

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
	 * @param control_system The control system
	 * @param robot The robot
	 */
	void initialize(std::shared_ptr<control::ControlSystem> control_system, 
					std::shared_ptr<robot::Robot> robot) override;

	/**
	 * @brief Run the autonomous
	 *
	 * @param clock The rtos clock
	 * @param delayer The rtos delayer
	 * @param control_system The control system
	 * @param robot The robot
	 */
	void run(std::shared_ptr<rtos::IClock> clock,
			 std::unique_ptr<rtos::IDelayer>& delayer,
			 std::shared_ptr<control::ControlSystem> control_system, 
			 std::shared_ptr<robot::Robot> robot) override;
};
}
}

#endif