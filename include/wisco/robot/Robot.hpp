#ifndef WISCO_ROBOT_ROBOT_HPP
#define WISCO_ROBOT_ROBOT_HPP

#include <memory>
#include <vector>

#include "ASubsystem.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief The namespace that holds all robot classes
 * @author Nathan Sandvig
 *
 */
namespace robot
{

/**
 * @brief A container class for subsystems
 * @author Nathan Sandvig
 *
 */
class Robot
{
private:
	/**
	 * @brief The subsystems contained in the robot
	 *
	 */
	std::vector<std::unique_ptr<ASubsystem>> subsystems{};

public:
	/**
	 * @brief Adds a subsystem to the robot
	 *
	 * @param subsystem The subsystem being added to the robot
	 */
	void addSubsystem(std::unique_ptr<ASubsystem>& subsystem);

	/**
	 * @brief Removes a subsystem from the robot
	 *
	 * @param subsystem_name The name of the subsystem to remove from the robot
	 * @return true The subsystem was removed
	 * @return false The subsystem was not contained in the robot
	 */
	bool removeSubsystem(std::string subsystem_name);

	/**
	 * @brief Initializes all subsystems in the robot
	 *
	 */
	void initialize();

	/**
	 * @brief Runs all subsystems in the robot
	 * 
	 */
	void run();	

	/**
	 * @brief Sends a command to a subsystem
	 *
	 * @param subsystem_name The name of the subsystem
	 * @param command_name The name of the command
	 * @param ... The parameters for the command
	 */
	void sendCommand(std::string subsystem_name, std::string command_name, ...);

	/**
	 * @brief Gets a state of a subsystem
	 *
	 * @param subsystem_name The name of the subsystem
	 * @param state_name The name of the state
	 * @return void* The current value of that state
	 */
	void* getState(std::string subsystem_name, std::string state_name);
};
} // namespace robot
} // namespace wisco

#endif