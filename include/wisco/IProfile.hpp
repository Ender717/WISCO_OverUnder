#ifndef WISCO_I_PROFILE_HPP
#define WISCO_I_PROFILE_HPP

#include <string>

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Interface for the profiles in the system
 * @author Nathan Sandvig
 *
 */
class IProfile
{
public:
	/**
	 * @brief Destroy the IProfile object
	 *
	 */
	virtual ~IProfile() = default;

	/**
	 * @brief Get the name of the profile
	 *
	 * @return std::string The name of the profile
	 */
	virtual std::string getName() = 0;

	/**
	 * @brief Get the chassis control mode
	 *
	 * @return std::string The chassis control mode
	 */
	virtual std::string getChassisControlMode() = 0;

	/**
	 * @brief Get the mapping of a control to digital inputs
	 *
	 * @return std::string The mapping of this control to a digital input
	 */
	virtual std::string getControlMapping(std::string control) = 0;
};

} // namespace wisco

#endif