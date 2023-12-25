#ifndef WISCO_AUTONOMOUS_MANAGER_HPP
#define WISCO_AUTONOMOUS_MANAGER_HPP

#include <memory>

#include "IAutonomous.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Manages the execution of the autonomous routine
 * @author Nathan Sandvig
 *
 */
class AutonomousManager
{
private:
	/**
	 * @brief The autonomous routine
	 *
	 */
	std::unique_ptr<IAutonomous> m_autonomous{};

public:
	/**
	 * @brief Set the autonomous routine
	 *
	 * @param autonomous The autonomous routine
	 */
	void setAutonomous(std::unique_ptr<IAutonomous>& autonomous);

	/**
	 * @brief Initialize the autonomous routine
	 *
	 * @param robot The robot being controlled
	 */
	void initializeAutonomous(std::shared_ptr<robot::Robot> robot);

	/**
	 * @brief Run the autonomous routine
	 *
	 * @param robot The robot being controlled
	 */
	void runAutonomous(std::shared_ptr<robot::Robot> robot);
};

} // namespace wisco

#endif