#ifndef WISCO_CONFIGS_BLUE_CONFIGURATION_HPP
#define WISCO_CONFIGS_BLUE_CONFIGURATION_HPP

// odometry includes
#include "pros_adapters/ProsClock.hpp"
#include "pros_adapters/ProsDelayer.hpp"
#include "pros_adapters/ProsHeading.hpp"
#include "pros_adapters/ProsMutex.hpp"
#include "pros_adapters/ProsRotation.hpp"
#include "pros_adapters/ProsTask.hpp"
#include "wisco/hal/TrackingWheel.hpp"
#include "wisco/robot/subsystems/position/InertialOdometryBuilder.hpp"
#include "wisco/robot/subsystems/position/PositionSubsystem.hpp"

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

public:
    /**
	 * @brief Get the name of the configuration
	 *
	 * @return std::string The name of the configuration
	 */
	std::string getName() override;

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