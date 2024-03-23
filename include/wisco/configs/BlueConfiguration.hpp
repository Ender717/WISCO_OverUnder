#ifndef WISCO_CONFIGS_BLUE_CONFIGURATION_HPP
#define WISCO_CONFIGS_BLUE_CONFIGURATION_HPP

// odometry includes
#include "pros/motors.h"
#include "pros_adapters/ProsClock.hpp"
#include "pros_adapters/ProsController.hpp"
#include "pros_adapters/ProsDelayer.hpp"
#include "pros_adapters/ProsHeading.hpp"
#include "pros_adapters/ProsMutex.hpp"
#include "pros_adapters/ProsRotation.hpp"
#include "pros_adapters/ProsTask.hpp"
#include "wisco/hal/TrackingWheel.hpp"
#include "wisco/robot/subsystems/position/InertialOdometryBuilder.hpp"
#include "wisco/robot/subsystems/position/PositionSubsystem.hpp"

// drive includes
#include "pros_adapters/ProsV5Motor.hpp"
#include "wisco/robot/subsystems/drive/DirectDifferentialDriveBuilder.hpp"
#include "wisco/robot/subsystems/drive/KinematicDifferentialDriveBuilder.hpp"
#include "wisco/robot/subsystems/drive/CurveVelocityProfile.hpp"
#include "wisco/robot/subsystems/drive/DifferentialDriveSubsystem.hpp"

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
	static constexpr int8_t DRIVE_LEFT_MOTOR_1_PORT{11};

	/**
	 * @brief The first left drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_LEFT_MOTOR_1_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The second left drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_LEFT_MOTOR_2_PORT{12};

	/**
	 * @brief The second left drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_LEFT_MOTOR_2_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The third left drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_LEFT_MOTOR_3_PORT{-13};

	/**
	 * @brief The third left drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_LEFT_MOTOR_3_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The fourth left drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_LEFT_MOTOR_4_PORT{-14};

	/**
	 * @brief The fourth left drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_LEFT_MOTOR_4_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The first right drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_RIGHT_MOTOR_1_PORT{17};

	/**
	 * @brief The first right drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_RIGHT_MOTOR_1_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The second right drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_RIGHT_MOTOR_2_PORT{18};

	/**
	 * @brief The second right drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_RIGHT_MOTOR_2_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The third right drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_RIGHT_MOTOR_3_PORT{-19};

	/**
	 * @brief The third right drive motor gearset
	 * 
	 */
	static constexpr pros::v5::MotorGears DRIVE_RIGHT_MOTOR_3_GEARSET{pros::E_MOTOR_GEARSET_06};

	/**
	 * @brief The fourth right drive motor port
	 * 
	 */
	static constexpr int8_t DRIVE_RIGHT_MOTOR_4_PORT{-20};

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