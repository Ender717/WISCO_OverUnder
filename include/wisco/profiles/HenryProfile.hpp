#ifndef WISCO_PROFILES_HENRY_PROFILE_HPP
#define WISCO_PROFILES_HENRY_PROFILE_HPP

#include <map>

#include "wisco/IProfile.hpp"

#include "wisco/user/EChassisControlMode.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for the available driver profiles
 * @author Nathan Sandvig
 *
 */
namespace profiles
{
/**
 * @brief Driver profile for Henry
 * @author Nathan Sandvig
 */
class HenryProfile : public IProfile
{
private:
    /**
     * @brief The name of the profile
     * 
     */
    static constexpr char PROFILE_NAME[]{"HENRY"};

    /**
     * @brief The control modes for the profile
     * 
     */
	const std::map<std::string, int> CONTROL_MODE_MAP
	{
		{"DRIVE", static_cast<int>(user::EChassisControlMode::SPLIT_ARCADE_LEFT)}
	};

    /**
     * @brief The mapping of the controls to the analog inputs
     * 
     */
    const std::map<std::string, user::EControllerAnalog> ANALOG_CONTROL_MAP{};

	/**
     * @brief The mapping of the controls to the digital inputs
     * 
     */
    const std::map<std::string, user::EControllerDigital> DIGITAL_CONTROL_MAP{};

public:
	/**
	 * @brief Get the name of the profile
	 *
	 * @return std::string The name of the profile
	 */
	std::string getName() override;

	/**
	 * @brief Get the control mode for a specific control type
	 * 
	 * @param control The control type
	 * @return int The control mode
	 */
	int getControlMode(std::string control) override;

	/**
	 * @brief Get the mapping of a control to analog inputs
	 *
	 * @return std::string The mapping of this control to an analog input
	 */
	user::EControllerAnalog getAnalogControlMapping(std::string control) override;

	/**
	 * @brief Get the mapping of a control to digital inputs
	 *
	 * @return std::string The mapping of this control to a digital input
	 */
	user::EControllerDigital getDigitalControlMapping(std::string control) override;
};
}
}

#endif