#ifndef WISCO_PROFILES_JOHN_PROFILE_HPP
#define WISCO_PROFILES_JOHN_PROFILE_HPP

#include <map>

#include "wisco/IProfile.hpp"

#include "wisco/user/drive/EChassisControlMode.hpp"
#include "wisco/user/elevator/EElevatorControlMode.hpp"
#include "wisco/user/hang/EHangControlMode.hpp"
#include "wisco/user/intake/EIntakeControlMode.hpp"
#include "wisco/user/loader/ELoaderControlMode.hpp"
#include "wisco/user/wings/EWingsControlMode.hpp"

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
 * @brief Driver profile for John
 * @author Nathan Sandvig
 */
class JohnProfile : public IProfile
{
private:
    /**
     * @brief The name of the profile
     * 
     */
    static constexpr char PROFILE_NAME[]{"JOHN"};

    /**
     * @brief The control modes for the profile
     * 
     */
	std::map<user::EControlType, int> CONTROL_MODE_MAP
	{
		{user::EControlType::DRIVE, static_cast<int>(user::drive::EChassisControlMode::TANK)},
		{user::EControlType::ELEVATOR, static_cast<int>(user::elevator::EElevatorControlMode::PRESET_TOGGLE_LADDER_INTAKE)},
		{user::EControlType::HANG, static_cast<int>(user::hang::EHangControlMode::PRESET_TOGGLE_LADDER)},
		{user::EControlType::INTAKE, static_cast<int>(user::intake::EIntakeControlMode::SPLIT_HOLD)},
		{user::EControlType::LOADER, static_cast<int>(user::loader::ELoaderControlMode::MACRO)},
		{user::EControlType::WINGS, static_cast<int>(user::wings::EWingsControlMode::DUAL_HOLD)}
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
		{user::EControl::HANG_NEXT, user::EControllerDigital::BUTTON_A},
		{user::EControl::HANG_PREVIOUS, user::EControllerDigital::BUTTON_B},
		{user::EControl::INTAKE_IN, user::EControllerDigital::TRIGGER_LEFT_TOP},
		{user::EControl::INTAKE_OUT, user::EControllerDigital::TRIGGER_LEFT_BOTTOM},
		{user::EControl::LOADER_TOGGLE, user::EControllerDigital::DPAD_LEFT},
		{user::EControl::WINGS_HOLD, user::EControllerDigital::SCUFF_RIGHT_REAR}
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