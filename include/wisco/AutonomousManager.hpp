#ifndef WISCO_AUTONOMOUS_MANAGER_HPP
#define WISCO_AUTONOMOUS_MANAGER_HPP

#include <memory>

#include "wisco/rtos/IClock.hpp"
#include "wisco/rtos/IDelayer.hpp"
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

public:
	/**
	 * @brief Construct a new AutonomousManager object
	 * 
	 * @param clock The rtos clock
	 * @param delayer The rtos delayer
	 */
	AutonomousManager(const std::shared_ptr<rtos::IClock>& clock, const std::unique_ptr<rtos::IDelayer>& delayer);

	/**
	 * @brief Set the autonomous routine
	 *
	 * @param autonomous The autonomous routine
	 */
	void setAutonomous(std::unique_ptr<IAutonomous>& autonomous);

	/**
	 * @brief Initialize the autonomous routine
	 *
	 * @param control_system The control system
	 * @param robot The robot being controlled
	 */
	void initializeAutonomous(std::shared_ptr<control::ControlSystem> control_system,
							  std::shared_ptr<robot::Robot> robot);

	/**
	 * @brief Run the autonomous routine
	 *
	 * @param control_system The control system
	 * @param robot The robot being controlled
	 */
	void runAutonomous(std::shared_ptr<control::ControlSystem> control_system,
					   std::shared_ptr<robot::Robot> robot);
};

} // namespace wisco

#endif