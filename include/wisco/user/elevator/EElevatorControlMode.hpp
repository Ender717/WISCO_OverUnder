#ifndef WISCO_USER_ELEVATOR_E_ELEVATOR_CONTROL_MODE_HPP
#define WISCO_USER_ELEVATOR_E_ELEVATOR_CONTROL_MODE_HPP

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
 * @brief Namespace for all elevator user control components
 * @author Nathan Sandvig
 * 
 */
namespace elevator
{

/**
 * @brief Defines all different elevator control formats
 * @author Nathan Sandvig
 * 
 */
enum class EElevatorControlMode
{
    MANUAL,
    PRESET_SPLIT,
    PRESET_TOGGLE_SINGLE,
    PRESET_TOGGLE_LADDER,
    PRESET_TOGGLE_LADDER_INTAKE
};
} // namespace elevator
} // namespace user
} // namespace wisco

#endif