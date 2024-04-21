#ifndef WISCO_I_AUTONOMOUS_HPP
#define WISCO_I_AUTONOMOUS_HPP

#include <memory>
#include <string>

#include "IAlliance.hpp"
#include "rtos/IClock.hpp"
#include "rtos/IDelayer.hpp"
#include "control/ControlSystem.hpp"
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
	 * @param control_system The control system
	 * @param robot The robot
	 */
	virtual void initialize(std::shared_ptr<control::ControlSystem> control_system, 
							std::shared_ptr<robot::Robot> robot) = 0;

	/**
	 * @brief Run the autonomous
	 *
	 * @param alliance The alliance
	 * @param clock The rtos clock
	 * @param delayer The rtos delayer
	 * @param control_system The control system
	 * @param robot The robot
	 */
	virtual void run(std::shared_ptr<IAlliance> alliance,
					 std::shared_ptr<rtos::IClock> clock,
					 std::unique_ptr<rtos::IDelayer>& delayer,
					 std::shared_ptr<control::ControlSystem> control_system, 
					 std::shared_ptr<robot::Robot> robot) = 0;
};

} // namespace wisco

#endif