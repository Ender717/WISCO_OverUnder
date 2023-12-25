#ifndef WISCO_I_AUTONOMOUS_HPP
#define WISCO_I_AUTONOMOUS_HPP

#include <memory>
#include <string>

#include "robot/Robot.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Interface for the autonomous routines in the system
 * @author Nathan Sandvig
 *
 */
class IAutonomous
{
public:
	/**
	 * @brief Destroy the IAutonomous object
	 *
	 */
	virtual ~IAutonomous() = default;

	/**
	 * @brief Get the name of the autonomous
	 *
	 * @return std::string The name of the autonomous
	 */
	virtual std::string getName() = 0;

	/**
	 * @brief Initialize the autonomous
	 *
	 */
	virtual void initialize(std::shared_ptr<robot::Robot> robot) = 0;

	/**
	 * @brief Run the autonomous
	 *
	 */
	virtual void run(std::shared_ptr<robot::Robot> robot) = 0;
};

} // namespace wisco

#endif