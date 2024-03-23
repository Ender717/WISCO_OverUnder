#ifndef WISCO_USER_E_CONTROLLER_DIGITAL_HPP
#define WISCO_USER_E_CONTROLLER_DIGITAL_HPP

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for all user interactive components
 * @author Nathan Sandvig
 * 
 */
namespace user
{

/**
 * @brief Defines all different controller digital inputs
 * @author Nathan Sandvig
 * 
 */
enum class EControllerDigital
{
    BUTTON_A,
    BUTTON_B,
    BUTTON_X,
    BUTTON_Y,
    DPAD_DOWN,
    DPAD_LEFT,
    DPAD_RIGHT,
    DPAD_UP,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT,
    SCUFF_LEFT_REAR,
    SCUFF_LEFT_UNDER,
    SCUFF_RIGHT_REAR,
    SCUFF_RIGHT_UNDER,
    TRIGGER_LEFT_BOTTOM,
    TRIGGER_LEFT_TOP,
    TRIGGER_RIGHT_BOTTOM,
    TRIGGER_RIGHT_TOP,
    NONE
};
} // namespace user
} // namespace wisco

#endif