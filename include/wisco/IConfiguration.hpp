#ifndef WISCO_I_CONFIGURATION_HPP
#define WISCO_I_CONFIGURATION_HPP

#include <memory>
#include <string>

#include "wisco/control/ControlSystem.hpp"
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
 * @brief Interface for the configurations in the system
 * @author Nathan Sandvig
 *
 */
class IConfiguration
{
public:
	/**
	 * @brief Destroy the IConfiguration object
	 *
	 */
	virtual ~IConfiguration() = default;

	/**
	 * @brief Get the name of the configuration
	 *
	 * @return std::string The name of the configuration
	 */
	virtual std::string getName() = 0;

	/**
	 * @brief Build a control system using this configuration
	 * 
	 * @return std::shared_ptr<control::ControlSystem> The control system built by this configuration
	 */
	virtual std::shared_ptr<control::ControlSystem> buildControlSystem() = 0;

	/**
	 * @brief Build a controller using this configuration
	 * 
	 * @return std::shared_ptr<user::IController> The controller build by this configuration
	 */
	virtual std::shared_ptr<user::IController> buildController() = 0;

	/**
	 * @brief Build a robot using this configuration
	 *
	 * @return robot::Robot The robot built by this configuration
	 */
	virtual std::shared_ptr<robot::Robot> buildRobot() = 0;
};
} // namespace wisco

#endif