#ifndef WISCO_CONFIGS_ORANGE_CONFIGURATION_HPP
#define WISCO_CONFIGS_ORANGE_CONFIGURATION_HPP

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

// hang includes
#include "pros_adapters/ProsPiston.hpp"
#include "wisco/robot/subsystems/hang/PistonClawBuilder.hpp"
#include "wisco/robot/subsystems/hang/PistonToggleArmBuilder.hpp"
#include "wisco/robot/subsystems/hang/PistonWinchBuilder.hpp"
#include "wisco/robot/subsystems/hang/HangSubsystem.hpp"

// intake includes
#include "pros_adapters/ProsVision.hpp"
#include "wisco/robot/subsystems/intake/PIDIntakeBuilder.hpp"
#include "wisco/robot/subsystems/intake/DistanceVisionBallDetectorBuilder.hpp"
#include "wisco/robot/subsystems/intake/IntakeSubsystem.hpp"

// elevator includes
#include "wisco/robot/subsystems/elevator/PIDElevatorBuilder.hpp"
#include "wisco/robot/subsystems/elevator/ElevatorSubsystem.hpp"

// loader includes
#include "wisco/robot/subsystems/loader/PIDLoaderBuilder.hpp"
#include "wisco/robot/subsystems/loader/LoaderSubsystem.hpp"

// umbrella includes
#include "wisco/robot/subsystems/umbrella/PistonUmbrellaBuilder.hpp"
#include "wisco/robot/subsystems/umbrella/UmbrellaSubsystem.hpp"

// wings includes
#include "wisco/robot/subsystems/wings/PistonWingsBuilder.hpp"
#include "wisco/robot/subsystems/wings/WingsSubsystem.hpp"

// boomerang includes
#include "wisco/control/boomerang/PIDBoomerangBuilder.hpp"
#include "wisco/control/boomerang/BoomerangControl.hpp"

// motion includes
#include "wisco/control/motion/PIDDriveStraightBuilder.hpp"
#include "wisco/control/motion/PIDGoToPointBuilder.hpp"
#include "wisco/control/motion/PIDTurnBuilder.hpp"
#include "wisco/control/motion/MotionControl.hpp"

// pure pursuit includes
#include "wisco/control/path/PIDPurePursuitBuilder.hpp"
#include "wisco/control/path/PathFollowingControl.hpp"

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
 * @brief The hardware configuration of the orange robot
 * @author Nathan Sandvig
 * 
 */
class OrangeConfiguration : public IConfiguration
{
private:
    /**
     * @brief The name of the configuration
     * 
     */
    static constexpr char CONFIGURATION_NAME[]{"ORANGE"};

	/**
	 * @brief The port for the odometry heading sensor
	 * 
	 */
	static constexpr int8_t ODOMETRY_HEADING_PORT{17};

	/**
	 * @brief The tuning constant for the odometry heading sensor
	 * 
	 */
	static constexpr double ODOMETRY_HEADING_TUNING_CONSTANT{1.014656};

	/**
	 * @brief The port for the odometry linear distance tracking sensor
	 * 
	 */
	static constexpr int8_t ODOMETRY_LINEAR_PORT{14};

	/**
	 * @brief The radius of the odometry linear distance tracking wheel
	 * 
	 */
	static constexpr double ODOMETRY_LINEAR_RADIUS{1.22};

	/**
	 * @brief The offset of the odometry linear distance tracking wheel
	 * 
	 */
	static constexpr double ODOMETRY_LINEAR_OFFSET{-3.35};

	/**
	 * @brief The port for the odometry strafe distance tracking sensor
	 * 
	 */
	static constexpr int8_t ODOMETRY_STRAFE_PORT{18};

	/**
	 * @brief The radius of the odometry strafe distance tracking wheel
	 * 
	 */
	static constexpr double ODOMETRY_STRAFE_RADIUS{-1.22};

	/**
	 * @brief The offset of the odometry strafe distance tracking wheel
	 * 
	 */
	static constexpr double ODOMETRY_STRAFE_OFFSET{4.6};

	/**
	 * @brief The port for the resetter distance sensor
	 * 
	 */
	static constexpr int8_t RESETTER_DISTANCE_PORT{16};

	/**
	 * @brief The tuning constant for the resetter distance sensor
	 * 
	 */
	static constexpr double RESETTER_DISTANCE_CONSTANT{1.0};

	/**
	 * @brief The tuning offset for the resetter distance sensor
	 * 
	 */
	static constexpr double RESETTER_DISTANCE_OFFSET{};

	/**
	 * @brief The x-offset of the resetter
	 * 
	 */
	static constexpr double RESETTER_OFFSET_X{-6.125};

	/**
	 * @brief The y-offset of the resetter
	 * 
	 */
	static constexpr double RESETTER_OFFSET_Y{-5.500};

	/**
	 * @brief The angle-offset of the resetter
	 * 
	 */
	static constexpr double RESETTER_OFFSET_THETA{-M_PI / 2};

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
	 * Current calculation = 12 volts to 58.707 inches per second
	 * 
	 */
	static constexpr double DRIVE_VELOCITY_TO_VOLTAGE{12.0 / 58.707};

	/**
	 * @brief The mass of the drive
	 * 
	 */
	static constexpr double DRIVE_MASS{9.89};

	/**
	 * @brief The radius of the drive
	 * 
	 */
	static constexpr double DRIVE_RADIUS{6.0625};//{6.5 * 2.54 / 100};

	/**
	 * @brief The moment of inertia of the drive
	 * 
	 */
	static constexpr double DRIVE_MOMENT_OF_INERTIA{19.887 * DRIVE_RADIUS * DRIVE_MASS};

	/**
	 * @brief The gear ratio of the drive
	 * 
	 */
	static constexpr double DRIVE_GEAR_RATIO{600.0 / 345.0};

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
	static constexpr int8_t INTAKE_MOTOR_1_PORT{19};

	/**
	 * @brief The first intake motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears INTAKE_MOTOR_1_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The radius of the intake roller
	 * 
	 */
	static constexpr double INTAKE_ROLLER_RADIUS{1};

	/**
	 * @brief The port for the ball detector distance sensor
	 * 
	 */
	static constexpr int8_t BALL_DETECTOR_DISTANCE_PORT{6};

	/**
	 * @brief The tuning constant for the ball detector distance sensor
	 * 
	 */
	static constexpr double BALL_DETECTOR_DISTANCE_CONSTANT{0.9769};

	/**
	 * @brief The tuning offset for the ball detector distance sensor
	 * 
	 */
	static constexpr double BALL_DETECTOR_DISTANCE_OFFSET{3.5193};

	/**
	 * @brief The port for the ball detector vision sensor
	 * 
	 */
	static constexpr int8_t BALL_DETECTOR_VISION_PORT{13};

	/**
	 * @brief The proportional constant for the boomerang linear pid controller
	 * 
	 */
	static constexpr double BOOMERANG_LINEAR_KP{14.0};

	/**
	 * @brief The integral constant for the boomerang linear pid controller
	 * 
	 */
	static constexpr double BOOMERANG_LINEAR_KI{};

	/**
	 * @brief The derivative constant for the boomerang linear pid controller
	 * 
	 */
	static constexpr double BOOMERANG_LINEAR_KD{1024.0};

	/**
	 * @brief The proportional constant for the boomerang rotational pid controller
	 * 
	 */
	static constexpr double BOOMERANG_ROTATIONAL_KP{640.0};

	/**
	 * @brief The integral constant for the boomerang rotational pid controller
	 * 
	 */
	static constexpr double BOOMERANG_ROTATIONAL_KI{0.0};

	/**
	 * @brief The derivative constant for the boomerang rotational pid controller
	 * 
	 */
	static constexpr double BOOMERANG_ROTATIONAL_KD{12000.0};

	/**
	 * @brief The lead ratio for the boomerang controller
	 * 
	 */
	static constexpr double BOOMERANG_LEAD{0.15};

	/**
	 * @brief The distance where boomerang stops aiming at the target point
	 * 
	 */
	static constexpr double BOOMERANG_AIM_DISTANCE{6.0};

	/**
	 * @brief The target tolerance for the boomerang controller
	 * 
	 */
	static constexpr double BOOMERANG_TARGET_TOLERANCE{3.0};

	/**
	 * @brief The target velocity for the boomerang controller
	 * 
	 */
	static constexpr double BOOMERANG_TARGET_VELOCITY{1.0};

	/**
	 * @brief The proportional constant for the drive straight linear pid controller
	 * 
	 */
	static constexpr double DRIVE_STRAIGHT_LINEAR_KP{12.0};

	/**
	 * @brief The integral constant for the drive straight linear pid controller
	 * 
	 */
	static constexpr double DRIVE_STRAIGHT_LINEAR_KI{};

	/**
	 * @brief The derivative constant for the drive straight linear pid controller
	 * 
	 */
	static constexpr double DRIVE_STRAIGHT_LINEAR_KD{800.0};

	/**
	 * @brief The proportional constant for the drive straight rotational pid controller
	 * 
	 */
	static constexpr double DRIVE_STRAIGHT_ROTATIONAL_KP{128.0};

	/**
	 * @brief The integral constant for the drive straight rotational pid controller
	 * 
	 */
	static constexpr double DRIVE_STRAIGHT_ROTATIONAL_KI{0.001};

	/**
	 * @brief The derivative constant for the drive straight rotational pid controller
	 * 
	 */
	static constexpr double DRIVE_STRAIGHT_ROTATIONAL_KD{800.0};

	/**
	 * @brief The target tolerance for the drive straight controller
	 * 
	 */
	static constexpr double DRIVE_STRAIGHT_TARGET_TOLERANCE{2.0};

	/**
	 * @brief The target velocity for the drive straight controller
	 * 
	 */
	static constexpr double DRIVE_STRAIGHT_TARGET_VELOCITY{1.0};

	/**
	 * @brief The proportional constant for the go to point linear pid controller
	 * 
	 */
	static constexpr double GO_TO_POINT_LINEAR_KP{4.8};

	/**
	 * @brief The integral constant for the go to point linear pid controller
	 * 
	 */
	static constexpr double GO_TO_POINT_LINEAR_KI{};

	/**
	 * @brief The derivative constant for the go to point linear pid controller
	 * 
	 */
	static constexpr double GO_TO_POINT_LINEAR_KD{300.0};

	/**
	 * @brief The proportional constant for the go to point rotational pid controller
	 * 
	 */
	static constexpr double GO_TO_POINT_ROTATIONAL_KP{1.3};

	/**
	 * @brief The integral constant for the go to point rotational pid controller
	 * 
	 */
	static constexpr double GO_TO_POINT_ROTATIONAL_KI{0.001};

	/**
	 * @brief The derivative constant for the go to point rotational pid controller
	 * 
	 */
	static constexpr double GO_TO_POINT_ROTATIONAL_KD{120.0};

	/**
	 * @brief The target tolerance for the go to point controller
	 * 
	 */
	static constexpr double GO_TO_POINT_TARGET_TOLERANCE{2.0};

	/**
	 * @brief The target velocity for the go to point controller
	 * 
	 */
	static constexpr double GO_TO_POINT_TARGET_VELOCITY{4.0};

	/**
	 * @brief The KP for the elevator PID
	 * 
	 */
	static constexpr double ELEVATOR_KP{24.0};

	/**
	 * @brief The KI for the elevator PID
	 * 
	 */
	static constexpr double ELEVATOR_KI{0.0};

	/**
	 * @brief The KD for the elevator PID
	 * 
	 */
	static constexpr double ELEVATOR_KD{256.0};

	/**
	 * @brief The first elevator motor port
	 * 
	 */
	static constexpr int8_t ELEVATOR_MOTOR_1_PORT{-11};

	/**
	 * @brief The first elevator motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears ELEVATOR_MOTOR_1_GEARSET{pros::E_MOTOR_GEARSET_36};

	/**
	 * @brief The second elevator motor port
	 * 
	 */
	static constexpr int8_t ELEVATOR_MOTOR_2_PORT{20};

	/**
	 * @brief The second elevator motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears ELEVATOR_MOTOR_2_GEARSET{pros::E_MOTOR_GEARSET_36};

	/**
	 * @brief The elevator rotation sensor port
	 * 
	 */
	static constexpr int8_t ELEVATOR_ROTATION_SENSOR_PORT{};

	/**
	 * @brief The number of inches moved per radian on the elevator
	 * 
	 */
	static constexpr double ELEVATOR_INCHES_PER_RADIAN{2 * 0.625};

	/**
	 * @brief The minimum position of the elevator
	 * 
	 */
	static constexpr double ELEVATOR_MINIMUM_POSITION{0};

	/**
	 * @brief The maximum position of the elevator
	 * 
	 */
	static constexpr double ELEVATOR_MAXIMUM_POSITION{16.5};

	/**
	 * @brief The elevator distance sensor port
	 * 
	 */
	static constexpr int8_t ELEVATOR_DISTANCE_PORT{};

	/**
	 * @brief The elevator distance sensor tuning constant
	 * 
	 */
	static constexpr double ELEVATOR_DISTANCE_CONSTANT{};

	/**
	 * @brief The elevator distance sensor tuning offset
	 * 
	 */
	static constexpr double ELEVATOR_DISTANCE_OFFSET{};

	/**
	 * @brief The first hang claw piston port
	 * 
	 */
	static constexpr char HANG_CLAW_PISTON_1_PORT{'E'};

	/**
	 * @brief The first hang claw piston's extended state
	 * 
	 */
	static constexpr bool HANG_CLAW_PISTON_1_EXTENDED_STATE{true};

	/**
	 * @brief The hang claw piston state when the claw is closed
	 * 
	 */
	static constexpr bool HANG_CLAW_CLOSED_STATE{true};

	/**
	 * @brief The first hang arm piston port
	 * 
	 */
	static constexpr char HANG_ARM_PISTON_1_PORT{'C'};

	/**
	 * @brief The first hang arm piston's extended state
	 * 
	 */
	static constexpr bool HANG_ARM_PISTON_1_EXTENDED_STATE{true};

	/**
	 * @brief The hang arm piston state when the arm is up
	 * 
	 */
	static constexpr bool HANG_ARM_UP_STATE{true};

	/**
	 * @brief The first hang winch piston port
	 * 
	 */
	static constexpr char HANG_WINCH_PISTON_1_PORT{'D'};

	/**
	 * @brief The first hang winch piston's extended state
	 * 
	 */
	static constexpr bool HANG_WINCH_PISTON_1_EXTENDED_STATE{true};

	/**
	 * @brief The hang winch piston state when the winch is engaged
	 * 
	 */
	static constexpr bool HANG_WINCH_ENGAGED_STATE{true};

		/**
	 * @brief The KP for the loader PID
	 * 
	 */
	static constexpr double LOADER_KP{32.0};

	/**
	 * @brief The KI for the loader PID
	 * 
	 */
	static constexpr double LOADER_KI{0.0};

	/**
	 * @brief The KD for the loader PID
	 * 
	 */
	static constexpr double LOADER_KD{700.0};

	/**
	 * @brief The first loader motor port
	 * 
	 */
	static constexpr int8_t LOADER_MOTOR_1_PORT{5};

	/**
	 * @brief The first loader motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears LOADER_MOTOR_1_GEARSET{pros::E_MOTOR_GEARSET_36};

	/**
	 * @brief The loader position when loaded
	 * 
	 */
	static constexpr double LOADER_LOADED_POSITION{10 * M_PI / 12};

	/**
	 * @brief The loader position when ready
	 * 
	 */
	static constexpr double LOADER_READY_POSITION{-M_PI / 72};

	/**
	 * @brief The loader position tolerance
	 * 
	 */
	static constexpr double LOADER_POSITION_TOLERANCE{M_PI / 18};

	/**
	 * @brief The proportional constant for the pure pursuit linear pid controller
	 * 
	 */
	static constexpr double PURE_PURSUIT_LINEAR_KP{12.0};

	/**
	 * @brief The integral constant for the pure pursuit linear pid controller
	 * 
	 */
	static constexpr double PURE_PURSUIT_LINEAR_KI{};

	/**
	 * @brief The derivative constant for the pure pursuit linear pid controller
	 * 
	 */
	static constexpr double PURE_PURSUIT_LINEAR_KD{640.0};

	/**
	 * @brief The proportional constant for the pure pursuit rotational pid controller
	 * 
	 */
	static constexpr double PURE_PURSUIT_ROTATIONAL_KP{640.0};

	/**
	 * @brief The integral constant for the pure pursuit rotational pid controller
	 * 
	 */
	static constexpr double PURE_PURSUIT_ROTATIONAL_KI{};

	/**
	 * @brief The derivative constant for the pure pursuit rotational pid controller
	 * 
	 */
	static constexpr double PURE_PURSUIT_ROTATIONAL_KD{10000.0};

	/**
	 * @brief The follow distance for the pure pursuit controller
	 * 
	 */
	static constexpr double PURE_PURSUIT_FOLLOW_DISTANCE{12.0};

	/**
	 * @brief The target tolerance for the pure pursuit controller
	 * 
	 */
	static constexpr double PURE_PURSUIT_TARGET_TOLERANCE{3.0};

	/**
	 * @brief The target velocity for the pure pursuit controller
	 * 
	 */
	static constexpr double PURE_PURSUIT_TARGET_VELOCITY{1.0};

	/**
	 * @brief The proportional constant for the turn pid controller
	 * 
	 */
	static constexpr double TURN_KP{180.0};

	/**
	 * @brief The integral constant for the turn pid controller
	 * 
	 */
	static constexpr double TURN_KI{};

	/**
	 * @brief The derivative constant for the turn pid controller
	 * 
	 */
	static constexpr double TURN_KD{10000.0};

	/**
	 * @brief The target tolerance for the turn controller
	 * 
	 */
	static constexpr double TURN_TARGET_TOLERANCE{M_PI / 45};

	/**
	 * @brief The target velocity for the turn controller
	 * 
	 */
	static constexpr double TURN_TARGET_VELOCITY{M_PI / 180};

	/**
	 * @brief The first umbrella piston port
	 * 
	 */
	static constexpr int8_t UMBRELLA_PISTON_1_PORT{'C'};

	/**
	 * @brief The first umbrella piston's extended state
	 * 
	 */
	static constexpr bool UMBRELLA_PISTON_1_EXTENDED_STATE{true};

	/**
	 * @brief The umbrella piston state when the umbrella is out
	 * 
	 */
	static constexpr bool UMBRELLA_OUT_STATE{true};

	/**
	 * @brief The first left wing piston port
	 * 
	 */
	static constexpr char LEFT_WING_PISTON_1_PORT{'B'};

	/**
	 * @brief The first left wing piston's extended state
	 * 
	 */
	static constexpr bool LEFT_WING_PISTON_1_EXTENDED_STATE{true};

	/**
	 * @brief The first right wing piston port
	 * 
	 */
	static constexpr char RIGHT_WING_PISTON_1_PORT{'A'};

	/**
	 * @brief The first right wing piston's extended state
	 * 
	 */
	static constexpr bool RIGHT_WING_PISTON_1_EXTENDED_STATE{true};

	/**
	 * @brief The wing piston state when the wings are out
	 * 
	 */
	static constexpr bool WINGS_OUT_STATE{true};

public:
    /**
	 * @brief Get the name of the configuration
	 *
	 * @return std::string The name of the configuration
	 */
	std::string getName() override;

	/**
	 * @brief Build a control system using this configuration
	 * 
	 * @return std::shared_ptr<control::ControlSystem> The control system built by this configuration
	 */
	std::shared_ptr<control::ControlSystem> buildControlSystem() override;

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