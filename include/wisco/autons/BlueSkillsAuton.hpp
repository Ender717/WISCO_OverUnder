#ifndef WISCO_AUTONS_BLUE_SKILLS_AUTON_HPP
#define WISCO_AUTONS_BLUE_SKILLS_AUTON_HPP

#include <cmath>
#include <cstdint>
#include <vector>

#include "pros_adapters/ProsMutex.hpp"
#include "pros_adapters/ProsTask.hpp"

#include "wisco/io/VisionObject.hpp"
#include "wisco/routines/SentryMode.hpp"
#include "wisco/utils/UtilityFunctions.hpp"
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
 * @brief The auton for the blue robot in skillses
 * @author Nathan Sandvig
 * 
 */
class BlueSkillsAuton : public IAutonomous
{
private:
	/**
	 * @brief The name of the autonomous
	 * 
	 */
	static constexpr char AUTONOMOUS_NAME[]{"S_BLUE"};

	/**
	 * @brief The delay for loops
	 * 
	 */
	static constexpr uint8_t LOOP_DELAY{10};

	/**
	 * @brief The maximum voltage setting
	 * 
	 */
	static constexpr double MAX_VOLTAGE{12.0};

	/**
	 * @brief The offset to the front of the robot for the elevator
	 * 
	 */
	static constexpr double ELEVATOR_OFFSET{6.5};

	/**
	 * @brief The elevator position tolerance
	 * 
	 */
	static constexpr double ELEVATOR_TOLERANCE{0.5};

	/**
	 * @brief The velocity for motions
	 * 
	 */
	static constexpr double MOTION_VELOCITY{36.0};

	/**
	 * @brief The velocity to be considered "stopped"
	 * 
	 */
	static constexpr double STOP_VELOCITY{6.0};

	/**
	 * @brief The velocity for turns
	 * 
	 */
	static constexpr double TURN_VELOCITY{2 * M_PI};
	
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
	 * @brief The control system
	 * 
	 */
	std::shared_ptr<control::ControlSystem> m_control_system{};

	/**
	 * @brief The robot
	 * 
	 */
	std::shared_ptr<robot::Robot> m_robot{};

	/**
	 * @brief Gets the rtos time
	 * 
	 * @return uint32_t The rtos time in millis
	 */
	uint32_t getTime();

	/**
	 * @brief Delays the rtos for a number of milliseconds
	 * 
	 * @param millis The delay duration in millis
	 */
	void delay(uint32_t millis);

	/**
	 * @brief Pauses the control system
	 * 
	 */
	void pauseControlSystem();

	/**
	 * @brief Resumes the control system
	 * 
	 */
	void resumeControlSystem();

	/**
	 * @brief Calls the boomerang go to point command
	 * 
	 * @param x The target x-coordinate
	 * @param y The target y-coordinate
	 * @param theta The target angle
	 * @param velocity The motion velocity
	 * @param timeout The milliseconds allowed before timing out
	 * @param tolerance The allowed tolerance to end the motion early
	 */
	void goToPoint(double x, double y, double theta, double velocity, uint32_t timeout = 0, double tolerance = 0.0);

	/**
	 * @brief Checks if the boomerang target has been reached
	 * 
	 * @return true The boomerang target has been reached
	 * @return false The boomerang target has not been reached
	 */
	bool boomerangTargetReached();

	/**
	 * @brief Drives straight
	 * 
	 * @param distance The distance to drive (negative = reverse)
	 * @param velocity The velocity to move
	 * @param timeout The milliseconds allowed before timing out
	 * @param tolerance The allowed tolerance to end the motion early
	 */
	void driveStraight(double distance, double velocity, uint32_t timeout = 0, double tolerance = 0.0);

	/**
	 * @brief Drives straight with a specified angle
	 * 
	 * @param distance The distance to drive (negative = reverse)
	 * @param velocity The velocity to move
	 * @param theta The angle to keep pointed forward
	 * @param timeout The milliseconds allowed before timing out
	 * @param tolerance The allowed tolerance to end the motion early
	 */
	void driveStraight(double distance, double velocity, double theta, uint32_t timeout = 0, double tolerance = 0.0);

	/**
	 * @brief Drives straight to a target point
	 * 
	 * @param x The target x-coordinate
	 * @param y The target y-coordinate
	 * @param velocity The motion velocity
	 * @param timeout The milliseconds allowed before timing out
	 * @param tolerance The allowed tolerance to end the motion
	 */
	void driveStraightToPoint(double x, double y, double velocity, uint32_t timeout = 0, double tolerance = 0.0);

	/**
	 * @brief Sets the velocity for DriveStraight
	 * 
	 * @param velocity The motion velocity
	 */
	void setDriveStraightVelocity(double velocity);

	/**
	 * @brief Checks if the drive straight target has been reached
	 * 
	 * @return true The drive straight target has been reached
	 * @return false The drive straight target has not been reached
	 */
	bool driveStraightTargetReached();

	/**
	 * @brief Calls the motion turn to angle command
	 * 
	 * @param theta The target angle
	 * @param velocity The turn velocity
	 * @param reversed Whether or not to turn to face away from the point
	 * @param timeout The milliseconds allowed before timing out
	 * @param tolerance The allowed tolerance to end the motion early
	 * @param direction The turn direction (default auto)
	 */
	void turnToAngle(double theta, double velocity, bool reversed = false, uint32_t timeout = 0, double tolerance = 0.0,
					 control::motion::ETurnDirection direction = control::motion::ETurnDirection::AUTO);

	/**
	 * @brief Calls the motion turn to point command
	 * 
	 * @param velocity The turn velocity
	 * @param x The target x-coordinate
	 * @param y The target y-coordinate
	 * @param reversed Whether or not to turn to face away from the point
	 * @param timeout The milliseconds allowed before timing out
	 * @param tolerance The allowed tolerance to end the motion early
	 * @param direction The turn direction (default auto)
	 */
	void turnToPoint(double x, double y, double velocity, bool reversed = false, uint32_t timeout = 0, double tolerance = 0.0,
					 control::motion::ETurnDirection direction = control::motion::ETurnDirection::AUTO);

	/**
	 * @brief Checks if the motion turn target has been reached
	 * 
	 * @return true The motion turn target has been reached
	 * @return false The motion turn target has not been reached
	 */
	bool turnTargetReached();

	/**
	 * @brief Calls the path following follow path command
	 * 
	 * @param path The path to follow
	 * @param velocity The path following velocity
	 */
	void followPath(std::vector<control::path::Point>& path, double velocity);

	/**
	 * @brief Sets the velocity of the path following system
	 * 
	 * @param velocity The path following velocity
	 */
	void setPathFollowingVelocity(double velocity);

	/**
	 * @brief Checks if the path following target has been reached
	 * 
	 * @return true The path following target has been reached
	 * @return false The path following target has not been reached
	 */
	bool pathFollowingTargetReached();

	/**
	 * @brief Set the velocity of the drive
	 * 
	 * @param left The left drive velocity
	 * @param right The right drive velocity
	 */
	void setDriveVelocity(double left, double right);

	/**
	 * @brief Set the voltage of the drive
	 * 
	 * @param left The left drive voltage
	 * @param right The right drive voltage
	 */
	void setDriveVoltage(double left, double right);

	/**
	 * @brief Gets the velocity of the drive
	 * 
	 * @return robot::subsystems::drive::Velocity The drive velocity
	 */
	robot::subsystems::drive::Velocity getDriveVelocity();

	/**
	 * @brief Gets the radius of the drive
	 * 
	 * @return double The drive radius
	 */
	double getDriveRadius();

	/**
	 * @brief Sets the position of the elevator
	 * 
	 * @param position The position of the elevator
	 * @param timeout The milliseconds allowed before timing out
	 */
	void setElevatorPosition(double position, uint32_t timeout = UINT32_MAX);

	/**
	 * @brief Calibrates the elevator
	 * 
	 */
	void calibrateElevator();

	/**
	 * @brief Gets the position of the elevator
	 * 
	 * @return double The position of the elevator
	 */
	double getElevatorPosition();

	/**
	 * @brief Checks if the elevator is calibrating
	 * 
	 * @return true The elevator is calibrating
	 * @return false The elevator is not calibrating
	 */
	bool elevatorIsCalibrating();

	/**
	 * @brief Get the distance to the hanging cap
	 * 
	 * @return double The distance to the hanging cap
	 */
	double getCapDistance();

	/**
	 * @brief Closes the claw
	 * 
	 */
	void closeClaw();

	/**
	 * @brief Opens the claw
	 * 
	 */
	void openClaw();

	/**
	 * @brief Raises the arm
	 * 
	 */
	void raiseArm();

	/**
	 * @brief Lowers the arm
	 * 
	 */
	void lowerArm();

	/**
	 * @brief Engages the winch
	 * 
	 */
	void engageWinch();

	/**
	 * @brief Disengages the winch
	 * 
	 */
	void disengageWinch();

	/**
	 * @brief Checks if the claw is closed
	 * 
	 * @return true The claw is closed
	 * @return false The claw is not closed
	 */
	bool clawClosed();

	/**
	 * @brief Checks if the claw is open
	 * 
	 * @return true The claw is open
	 * @return false The claw is not open
	 */
	bool clawOpen();

	/**
	 * @brief Checks if the arm is raised
	 * 
	 * @return true The arm is raised
	 * @return false The arm is not raised
	 */
	bool armRaised();

	/**
	 * @brief Checks if the arm is lowered
	 * 
	 * @return true The arm is lowered
	 * @return false The arm is not lowered
	 */
	bool armLowered();

	/**
	 * @brief Checks if the winch is engaged
	 * 
	 * @return true The winch is engaged
	 * @return false The winch is not engaged
	 */
	bool winchEngaged();

	/**
	 * @brief Checks if the winch is disengaged
	 * 
	 * @return true The winch is disengaged
	 * @return false The winch is not disengaged
	 */
	bool winchDisengaged();

	/**
	 * @brief Sets the velocity of the intake
	 * 
	 * @param velocity The velocity of the intake
	 */
	void setIntakeVelocity(double velocity);

	/**
	 * @brief Sets the voltage of the intake
	 * 
	 * @param voltage The voltage of the intake
	 */
	void setIntakeVoltage(double voltage);

	/**
	 * @brief Gets the velocity of the intake
	 * 
	 * @return double The velocity of the intake
	 */
	double getIntakeVelocity();

	/**
	 * @brief Gets the distance to the ball
	 * 
	 * @return double The distance to the ball
	 */
	double getBallDistance();

	/**
	 * @brief Gets the vision objects of the balls
	 * 
	 * @return std::vector<io::VisionObject> The ball vision object
	 */
	std::vector<io::VisionObject> getBallVisionObjects();

	/**
	 * @brief Loads the loader
	 * 
	 */
	void loadLoader();

	/**
	 * @brief Readies the loader
	 * 
	 */
	void readyLoader();

	/**
	 * @brief Checks if the loader is loaded
	 * 
	 * @return true The loader is loaded
	 * @return false The loader is not loaded
	 */
	bool isLoaderLoaded();

	/**
	 * @brief Checks if the loader is ready
	 * 
	 * @return true The loader is ready
	 * @return false The loader is not ready
	 */
	bool isLoaderReady();

	/**
	 * @brief Sets the odometry position
	 * 
	 * @param x The x-coordinate
	 * @param y The y-coordinate
	 * @param theta The angle
	 */
	void setOdometryPosition(double x, double y, double theta);

	/**
	 * @brief Sets the x-coordinate of the odometry
	 * 
	 * @param x The x-coordinate of the odometry
	 */
	void setOdometryX(double x);

	/**
	 * @brief Sets the y-coordinate of the odometry
	 * 
	 * @param y The y-coordinate of the odometry
	 */
	void setOdometryY(double y);

	/**
	 * @brief Sets the angle of the odometry
	 * 
	 * @param theta The angle of the odometry
	 */
	void setOdometryTheta(double theta);

	/**
	 * @brief Resets the x-coordinate of the odometry
	 * 
	 */
	void resetOdometryX();

	/**
	 * @brief Resets the y-coordinate of the odometry
	 * 
	 */
	void resetOdometryY();

	/**
	 * @brief Gets the odometry position
	 * 
	 * @return robot::subsystems::position::Position The odometry position
	 */
	robot::subsystems::position::Position getOdometryPosition();

	/**
	 * @brief Gets the odometry velocity
	 * 
	 * @return double The odometry velocity
	 */
	double getOdometryVelocity();

	/**
	 * @brief Sets the umbrella to in
	 * 
	 */
	void setUmbrellaIn();

	/**
	 * @brief Sets the umbrella to out
	 * 
	 */
	void setUmbrellaOut();

	/**
	 * @brief Checks if the umbrella is in
	 * 
	 * @return true The umbrella is in
	 * @return false The umbrella is not in
	 */
	bool isUmbrellaIn();

	/**
	 * @brief Checks if the umbrella is out
	 * 
	 * @return true The umbrella is out
	 * @return false The umbrella is not out
	 */
	bool isUmbrellaOut();

	/**
	 * @brief Sets the position of the left wing
	 * 
	 * @param out Whether or not the left wing is out
	 */
	void setLeftWing(bool out);

	/**
	 * @brief Sets the position of the right wing
	 * 
	 * @param out Whether or not the right wing is out
	 */
	void setRightWing(bool out);

	/**
	 * @brief Checks if the left wing is out
	 * 
	 * @return true The left wing is out
	 * @return false The left wing is not out
	 */
	bool isLeftWingOut();

	/**
	 * @brief Checks if the right wing is out
	 * 
	 * @return true The right wing is out
	 * @return false The right wing is not out
	 */
	bool isRightWingOut();

	/**
	 * @brief The path through the alley
	 * 
	 */
	std::vector<control::path::Point> alley_path{};

	/**
	 * @brief The path to come back through the alley
	 * 
	 */
	std::vector<control::path::Point> alley_return_path{};

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
	 * @param alliance The alliance
	 * @param clock The rtos clock
	 * @param delayer The rtos delayer
	 * @param control_system The control system
	 * @param robot The robot
	 */
	void run(std::shared_ptr<IAlliance> alliance,
			 std::shared_ptr<rtos::IClock> clock,
			 std::unique_ptr<rtos::IDelayer>& delayer,
			 std::shared_ptr<control::ControlSystem> control_system, 
			 std::shared_ptr<robot::Robot> robot) override;
};
}
}

#endif