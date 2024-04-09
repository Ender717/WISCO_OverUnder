#ifndef WISCO_CONFIGS_BLUE_CONFIGURATION_HPP
#define WISCO_CONFIGS_BLUE_CONFIGURATION_HPP

// odometry includes
#include "pros/motors.h"
#include "pros_adapters/ProsClock.hpp"
#include "pros_adapters/ProsController.hpp"
#include "pros_adapters/ProsDelayer.hpp"
#include "pros_adapters/ProsDistance.hpp"
#include "pros_adapters/ProsHeading.hpp"
#include "pros_adapters/ProsMutex.hpp"
#include "pros_adapters/ProsRotation.hpp"
#include "pros_adapters/ProsTask.hpp"
#include "wisco/hal/TrackingWheel.hpp"
#include "wisco/robot/subsystems/position/InertialOdometryBuilder.hpp"
#include "wisco/robot/subsystems/position/DistancePositionResetterBuilder.hpp"
#include "wisco/robot/subsystems/position/PositionSubsystem.hpp"

// drive includes
#include "pros_adapters/ProsV5Motor.hpp"
#include "wisco/robot/subsystems/drive/DirectDifferentialDriveBuilder.hpp"
#include "wisco/robot/subsystems/drive/KinematicDifferentialDriveBuilder.hpp"
#include "wisco/robot/subsystems/drive/CurveVelocityProfile.hpp"
#include "wisco/robot/subsystems/drive/DifferentialDriveSubsystem.hpp"

// intake includes
#include "wisco/robot/subsystems/intake/PIDIntakeBuilder.hpp"
#include "wisco/robot/subsystems/intake/DistanceVisionBallDetectorBuilder.hpp"
#include "wisco/robot/subsystems/intake/IntakeSubsystem.hpp"

// elevator includes
#include "wisco/robot/subsystems/elevator/PIDElevatorBuilder.hpp"
#include "wisco/robot/subsystems/elevator/ElevatorSubsystem.hpp"

#include "wisco/IConfiguration.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for hardware configurations
 * @author Nathan Sandvig
 * 
 */
namespace configs
{

/**
 * @brief The hardware configuration of the blue robot
 * @author Nathan Sandvig
 * 
 */
class BlueConfiguration : public IConfiguration
{
private:
    /**
     * @brief The name of the configuration
     * 
     */
    static constexpr char CONFIGURATION_NAME[]{"BLUE"};

	/**
	 * @brief The port for the odometry heading sensor
	 * 
	 */
	static constexpr int8_t ODOMETRY_HEADING_PORT{9};

	/**
	 * @brief The tuning constant for the odometry heading sensor
	 * 
	 */
	static constexpr double ODOMETRY_HEADING_TUNING_CONSTANT{1.014};

	/**
	 * @brief The port for the odometry linear distance tracking sensor
	 * 
	 */
	static constexpr uint8_t ODOMETRY_LINEAR_PORT{8};

	/**
	 * @brief The radius of the odometry linear distance tracking wheel
	 * 
	 */
	static constexpr double ODOMETRY_LINEAR_RADIUS{1.22};

	/**
	 * @brief The offset of the odometry linear distance tracking wheel
	 * 
	 */
	static constexpr double ODOMETRY_LINEAR_OFFSET{3.35};

	/**
	 * @brief The port for the odometry strafe distance tracking sensor
	 * 
	 */
	static constexpr uint8_t ODOMETRY_STRAFE_PORT{2};

	/**
	 * @brief The radius of the odometry strafe distance tracking wheel
	 * 
	 */
	static constexpr double ODOMETRY_STRAFE_RADIUS{1.22};

	/**
	 * @brief The offset of the odometry strafe distance tracking wheel
	 * 
	 */
	static constexpr double ODOMETRY_STRAFE_OFFSET{4.6};

	/**
	 * @brief The port for the resetter distance sensor
	 * 
	 */
	static constexpr int8_t RESETTER_DISTANCE_PORT{};

	/**
	 * @brief The tuning constant for the resetter distance sensor
	 * 
	 */
	static constexpr double RESETTER_DISTANCE_CONSTANT{};

	/**
	 * @brief The tuning offset for the resetter distance sensor
	 * 
	 */
	static constexpr double RESETTER_DISTANCE_OFFSET{};

	/**
	 * @brief The x-offset of the resetter
	 * 
	 */
	static constexpr double RESETTER_OFFSET_X{};

	/**
	 * @brief The y-offset of the resetter
	 * 
	 */
	static constexpr double RESETTER_OFFSET_Y{};

	/**
	 * @brief The angle-offset of the resetter
	 * 
	 */
	static constexpr double RESETTER_OFFSET_THETA{};

	/**
	 * @brief Whether to use the kinematic drive model or not
	 * 
	 */
	static constexpr bool DRIVE_KINEMATIC{false};

	/**
	 * @brief The jerk rate of the drive velocity profile
	 * 
	 */
	static constexpr double DRIVE_VELOCITY_PROFILE_JERK_RATE{20.0};

	/**
	 * @brief The maximum acceleration of the drive velocity profile
	 * 
	 */
	static constexpr double DRIVE_VELOCITY_PROFILE_MAX_ACCELERATION{5.0};

	/**
	 * @brief The first left drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_LEFT_MOTOR_1_PORT{-1};

	/**
	 * @brief The first left drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_LEFT_MOTOR_1_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The second left drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_LEFT_MOTOR_2_PORT{-2};

	/**
	 * @brief The second left drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_LEFT_MOTOR_2_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The third left drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_LEFT_MOTOR_3_PORT{3};

	/**
	 * @brief The third left drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_LEFT_MOTOR_3_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The fourth left drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_LEFT_MOTOR_4_PORT{4};

	/**
	 * @brief The fourth left drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_LEFT_MOTOR_4_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The first right drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_RIGHT_MOTOR_1_PORT{-7};

	/**
	 * @brief The first right drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_RIGHT_MOTOR_1_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The second right drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_RIGHT_MOTOR_2_PORT{-8};

	/**
	 * @brief The second right drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_RIGHT_MOTOR_2_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The third right drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_RIGHT_MOTOR_3_PORT{9};

	/**
	 * @brief The third right drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_RIGHT_MOTOR_3_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The fourth right drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_RIGHT_MOTOR_4_PORT{10};

	/**
	 * @brief The fourth right drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_RIGHT_MOTOR_4_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The conversion from velocity to voltage on the drive
	 * Current calculation = 12 volts to 1.43 meters per second
	 * 
	 */
	static constexpr double DRIVE_VELOCITY_TO_VOLTAGE{12.0 / 1.43};

	/**
	 * @brief The mass of the drive
	 * 
	 */
	static constexpr double DRIVE_MASS{9.89};

	/**
	 * @brief The radius of the drive
	 * 
	 */
	static constexpr double DRIVE_RADIUS{6.5 * 2.54 / 100};

	/**
	 * @brief The moment of inertia of the drive
	 * 
	 */
	static constexpr double DRIVE_MOMENT_OF_INERTIA{19.887 * DRIVE_RADIUS * DRIVE_MASS};

	/**
	 * @brief The gear ratio of the drive
	 * 
	 */
	static constexpr double DRIVE_GEAR_RATIO{600.0 / 331.4};

	/**
	 * @brief The wheel radius of the drive
	 * 
	 */
	static constexpr double DRIVE_WHEEL_RADIUS{3.25 * 2.54 / 100};

	/**
	 * @brief The KP for the intake PID
	 * 
	 */
	static constexpr double INTAKE_KP{1.0};

	/**
	 * @brief The KI for the intake PID
	 * 
	 */
	static constexpr double INTAKE_KI{0.0};

	/**
	 * @brief The KD for the intake PID
	 * 
	 */
	static constexpr double INTAKE_KD{0.0};

	/**
	 * @brief The first intake motor port
	 * 
	 */
	static constexpr int8_t INTAKE_MOTOR_1_PORT{-12};

	/**
	 * @brief The first intake motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears INTAKE_MOTOR_1_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The second intake motor port
	 * 
	 */
	static constexpr int8_t INTAKE_MOTOR_2_PORT{19};

	/**
	 * @brief The second intake motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears INTAKE_MOTOR_2_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The radius of the intake roller
	 * 
	 */
	static constexpr double INTAKE_ROLLER_RADIUS{1};

	/**
	 * @brief The port for the ball detector distance sensor
	 * 
	 */
	static constexpr int8_t BALL_DETECTOR_DISTANCE_PORT{};

	/**
	 * @brief The tuning constant for the ball detector distance sensor
	 * 
	 */
	static constexpr double BALL_DETECTOR_DISTANCE_CONSTANT{};

	/**
	 * @brief The tuning offset for the ball detector distance sensor
	 * 
	 */
	static constexpr double BALL_DETECTOR_DISTANCE_OFFSET{};

	/**
	 * @brief The KP for the elevator PID
	 * 
	 */
	static constexpr double ELEVATOR_KP{6.0};

	/**
	 * @brief The KI for the elevator PID
	 * 
	 */
	static constexpr double ELEVATOR_KI{0.0};

	/**
	 * @brief The KD for the elevator PID
	 * 
	 */
	static constexpr double ELEVATOR_KD{0.0};

	/**
	 * @brief The first elevator motor port
	 * 
	 */
	static constexpr int8_t ELEVATOR_MOTOR_1_PORT{-11};

	/**
	 * @brief The first elevator motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears ELEVATOR_MOTOR_1_GEARSET{pros::E_MOTOR_GEARSET_18};

	/**
	 * @brief The second elevator motor port
	 * 
	 */
	static constexpr int8_t ELEVATOR_MOTOR_2_PORT{20};

	/**
	 * @brief The second elevator motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears ELEVATOR_MOTOR_2_GEARSET{pros::E_MOTOR_GEARSET_18};

	/**
	 * @brief The elevator rotation sensor port
	 * 
	 */
	static constexpr int8_t ELEVATOR_ROTATION_SENSOR_PORT{};

	/**
	 * @brief The number of inches moved per radian on the elevator
	 * 
	 */
	static constexpr double ELEVATOR_INCHES_PER_RADIAN{17.0 / (0.8 * 2 * M_PI)};

public:
    /**
	 * @brief Get the name of the configuration
	 *
	 * @return std::string The name of the configuration
	 */
	std::string getName() override;

	/**
	 * @brief Build a controller using this configuration
	 * 
	 * @return std::shared_ptr<user::IController> The controller build by this configuration
	 */
	std::shared_ptr<user::IController> buildController() override;

	/**
	 * @brief Build a robot using this configuration
	 *
	 * @return robot::Robot The robot built by this configuration
	 */
	std::shared_ptr<robot::Robot> buildRobot() override;
};
}
}

#endif