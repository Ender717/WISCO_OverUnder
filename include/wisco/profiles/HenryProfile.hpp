#ifndef WISCO_PROFILES_HENRY_PROFILE_HPP
#define WISCO_PROFILES_HENRY_PROFILE_HPP

#include <map>

#include "wisco/IProfile.hpp"

#include "wisco/user/EChassisControlMode.hpp"
#include "wisco/user/EElevatorControlMode.hpp"
#include "wisco/user/EIntakeControlMode.hpp"

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
	std::map<user::EControlType, int> CONTROL_MODE_MAP
	{
		{user::EControlType::DRIVE, static_cast<int>(user::EChassisControlMode::SPLIT_ARCADE_LEFT)},
		{user::EControlType::ELEVATOR, static_cast<int>(user::EElevatorControlMode::PRESET_TOGGLE_LADDER_INTAKE)},
		{user::EControlType::INTAKE, static_cast<int>(user::EIntakeControlMode::SPLIT_HOLD)}
	};

    /**
     * @brief The mapping of the controls to the analog inputs
     * 
     */
    const std::map<user::EControl, user::EControllerAnalog> ANALOG_CONTROL_MAP{};

	/**
     * @brief The mapping of the controls to the digital inputs
     * 
     */
    const std::map<user::EControl, user::EControllerDigital> DIGITAL_CONTROL_MAP
	{
		{user::EControl::ELEVATOR_IN, user::EControllerDigital::TRIGGER_RIGHT_BOTTOM},
		{user::EControl::ELEVATOR_OUT, user::EControllerDigital::TRIGGER_RIGHT_TOP},
		{user::EControl::INTAKE_IN, user::EControllerDigital::TRIGGER_LEFT_TOP},
		{user::EControl::INTAKE_OUT, user::EControllerDigital::TRIGGER_LEFT_BOTTOM}
	};

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
	 * @param control_type The control type
	 * @return int The control mode
	 */
	int getControlMode(user::EControlType control_type) const override;

	/**
	 * @brief Set the control mode for a specific control type
	 * 
	 * @param control_type The control type
	 * @param control_mode The control mode
	 */
	void setControlMode(user::EControlType control_type, int control_mode) override;

	/**
	 * @brief Get the mapping of a control to analog inputs
	 *
	 * @param control The control
	 * @return user::EControllerAnalog The mapping of this control to a analog input
	 */
	user::EControllerAnalog getAnalogControlMapping(user::EControl control) const override;

	/**
	 * @brief Get the mapping of a control to digital inputs
	 *
	 * @param control The control
	 * @return user::EControllerDigital The mapping of this control to a digital input
	 */
	user::EControllerDigital getDigitalControlMapping(user::EControl control) const override;
};
}
}

#endif