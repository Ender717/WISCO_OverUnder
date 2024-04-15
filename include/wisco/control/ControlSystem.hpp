#ifndef WISCO_CONTROL_CONTROL_SYSTEM_HPP
#define WISCO_CONTROL_CONTROL_SYSTEM_HPP

#include <cstdarg>
#include <memory>
#include <vector>

#include "AControl.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for control algorithms
 * @author Nathan Sandvig
 * 
 */
namespace control
{

/**
 * @brief A container class for controls
 * @author Nathan Sandvig
 * 
 */
class ControlSystem
{
private:
	/**
	 * @brief The controls contained in the robot
	 *
	 */
	std::vector<std::unique_ptr<AControl>> controls{};

public:
	/**
	 * @brief Adds a control to the robot
	 *
	 * @param control The control being added to the robot
	 */
	void addControl(std::unique_ptr<AControl>& control);

	/**
	 * @brief Removes a control from the robot
	 *
	 * @param control_name The name of the control to remove from the robot
	 * @return true The control was removed
	 * @return false The control was not contained in the robot
	 */
	bool removeControl(std::string control_name);

	/**
	 * @brief Initializes all controls in the robot
	 *
	 */
	void initialize();

	/**
	 * @brief Sends a command to a control
	 *
	 * @param control_name The name of the control
	 * @param command_name The name of the command
	 * @param ... The parameters for the command
	 */
	void sendCommand(std::string control_name, std::string command_name, ...);

	/**
	 * @brief Gets a state of a control
	 *
	 * @param control_name The name of the control
	 * @param state_name The name of the state
	 * @return void* The current value of that state
	 */
	void* getState(std::string control_name, std::string state_name);
};
} // namespace control
} // namespace wisco

#endif