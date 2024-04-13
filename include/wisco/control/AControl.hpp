#ifndef WISCO_CONTROL_A_CONTROL_HPP
#define WISCO_CONTROL_A_CONTROL_HPP

#include <string>

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
 * @brief An abstract class for control algorithms
 * @author Nathan Sandvig
 * 
 */
class AControl
{
private:
	/**
	 * @brief The name of the control
	 *
	 */
	std::string m_name{};

public:
	/**
	 * @brief Construct a new AControl object
	 *
	 */
	AControl() = default;

	/**
	 * @brief Construct a new AControl object
	 *
	 * @param other The AControl object being copied
	 */
	AControl(const AControl& other) = default;

	/**
	 * @brief Construct a new AControl object
	 *
	 * @param other The AControl object being moved
	 */
	AControl(AControl&& other) = default;

	/**
	 * @brief Construct a new AControl object
	 *
	 * @param name The name of the control
	 */
	AControl(std::string name) : m_name{name} {}

	/**
	 * @brief Destroy the AControl object
	 *
	 */
	virtual ~AControl() = default;

	/**
	 * @brief Get the name of the control
	 *
	 * @return const std::string& The name of the control
	 */
	const std::string& getName() const
	{
		return m_name;
	}

	/**
	 * @brief Initializes the control
	 *
	 */
	virtual void initialize() = 0;

	/**
	 * @brief Runs the control
	 * 
	 */
	virtual void run() = 0;

	/**
	 * @brief Runs a command for the control
	 *
	 * @param command_name The name of the command to run
	 * @param args The parameters for the command
	 */
	virtual void command(std::string command_name, va_list& args) = 0;

	/**
	 * @brief Gets a state of the control
	 *
	 * @param state_name The name of the state to get
	 * @return void* The current value of that state
	 */
	virtual void* state(std::string state_name) = 0;

	/**
	 * @brief Copy assignment operator for AControl
	 *
	 * @param rhs The AControl on the right hand side of the operator
	 * @return AControl& This AControl with the copied values
	 */
	AControl& operator=(const AControl& rhs) = default;

	/**
	 * @brief Move assignment operator for AControl
	 *
	 * @param rhs The AControl value on the right hand side of the operator
	 * @return AControl& This AControl with the moved values
	 */
	AControl& operator=(AControl&& rhs) = default;
};
} // namespace control
} // namespace wisco

#endif