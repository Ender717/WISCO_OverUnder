#ifndef WISCO_USER_E_CONTROLLER_ANALOG_HPP
#define WISCO_USER_E_CONTROLLER_ANALOG_HPP

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
 * @brief Defines all different controller analog inputs
 * @author Nathan Sandvig
 * 
 */
enum class EControllerAnalog
{
    JOYSTICK_LEFT_X,
    JOYSTICK_LEFT_Y,
    JOYSTICK_RIGHT_X,
    JOYSTICK_RIGHT_Y,
    TRIGGER_LEFT,
    TRIGGER_RIGHT,
    NONE
};
} // namespace user
} // namespace wisco

#endif