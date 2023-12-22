#ifndef A_SUBSYSTEM_HPP
#define A_SUBSYSTEM_HPP

#include <string>

/**
 * @brief The namespace that holds all robot classes
 * @author Nathan Sandvig
 *
 */
namespace robot
{

/**
 * @brief An abstract class for robot subsystems
 * @author Nathan Sandvig
 *
 */
class ASubsystem
{
private:
	/**
	 * @brief The name of the subsystem
	 *
	 */
	std::string m_name{};

public:
	/**
	 * @brief Construct a new ASubsystem object
	 *
	 */
	ASubsystem() = default;

	/**
	 * @brief Construct a new ASubsystem object
	 *
	 * @param other The ASubsystem object being copied
	 */
	ASubsystem(const ASubsystem& other) = default;

	/**
	 * @brief Construct a new ASubsystem object
	 *
	 * @param other The ASubsystem object being moved
	 */
	ASubsystem(ASubsystem&& other) = default;

	/**
	 * @brief Construct a new ASubsystem object
	 *
	 * @param name The name of the subsystem
	 */
	ASubsystem(std::string name) : m_name{name} {}

	/**
	 * @brief Destroy the ASubsystem object
	 *
	 */
	virtual ~ASubsystem() = default;

	/**
	 * @brief Get the name of the subsystem
	 *
	 * @return const std::string& The name of the subsystem
	 */
	const std::string& getName() const;

	/**
	 * @brief Initializes the subsystem
	 *
	 */
	virtual void initialize();

	/**
	 * @brief Runs a command for the subsystem
	 *
	 * @param command_name The name of the command to run
	 * @param ... The parameters for the command
	 */
	virtual void command(std::string command_name, ...);

	/**
	 * @brief Gets a state of the subsystem
	 *
	 * @param state_name The name of the state to get
	 * @return void* The current value of that state
	 */
	virtual void* state(std::string state_name);

	/**
	 * @brief Copy assignment operator for ASubsystem
	 *
	 * @param rhs The ASubsystem on the right hand side of the operator
	 * @return ASubsystem& This ASubsystem with the copied values
	 */
	ASubsystem& operator=(const ASubsystem& rhs) = default;

	/**
	 * @brief Move assignment operator for ASubsystem
	 *
	 * @param rhs The ASubsystem value on the right hand side of the operator
	 * @return ASubsystem& This ASubsystem with the moved values
	 */
	ASubsystem& operator=(ASubsystem&& rhs) = default;
};
}

#endif