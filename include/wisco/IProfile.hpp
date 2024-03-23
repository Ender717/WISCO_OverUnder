#ifndef WISCO_I_PROFILE_HPP
#define WISCO_I_PROFILE_HPP

#include <string>

#include "wisco/user/EControllerAnalog.hpp"
#include "wisco/user/EControllerDigital.hpp"

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
	 * @brief Get the control mode for a specific control type
	 * 
	 * @param control The control type
	 * @return int The control mode
	 */
	virtual int getControlMode(std::string control) = 0;

	/**
	 * @brief Get the mapping of a control to analog inputs
	 *
	 * @return user::EControllerAnalog The mapping of this control to a analog input
	 */
	virtual user::EControllerAnalog getAnalogControlMapping(std::string control) = 0;

	/**
	 * @brief Get the mapping of a control to digital inputs
	 *
	 * @return user::EControllerDigital The mapping of this control to a digital input
	 */
	virtual user::EControllerDigital getDigitalControlMapping(std::string control) = 0;
};

} // namespace wisco

#endif