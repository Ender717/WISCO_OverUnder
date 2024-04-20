#ifndef WISCO_USER_E_CONTROL_HPP
#define WISCO_USER_E_CONTROL_HPP

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
 * @brief Defines all different control inputs
 * @author Nathan Sandvig
 * 
 */
enum class EControl
{
    ELEVATOR_CALIBRATE,
    ELEVATOR_IN,
    ELEVATOR_FIELD,
    ELEVATOR_MATCH_LOAD,
    ELEVATOR_POLE_HANG,
    ELEVATOR_PARTNER_HANG,
    ELEVATOR_OUT,
    ELEVATOR_TOGGLE,
    HANG_GRAB,
    HANG_HANG,
    HANG_INACTIVE,
    HANG_NEXT,
    HANG_PREVIOUS,
    HANG_RAISE,
    HANG_RESET,
    HANG_TOGGLE,
    INTAKE_IN,
    INTAKE_OUT,
    INTAKE_TOGGLE,
    LOADER_HOLD,
    LOADER_LOAD,
    LOADER_READY,
    LOADER_TOGGLE,
    UMBRELLA_HOLD,
    UMBRELLA_IN,
    UMBRELLA_OUT,
    UMBRELLA_TOGGLE,
    WINGS_HOLD,
    WINGS_IN,
    WINGS_OUT,
    WINGS_TOGGLE,
    WINGS_LEFT_HOLD,
    WINGS_LEFT_IN,
    WINGS_LEFT_OUT,
    WINGS_LEFT_TOGGLE,
    WINGS_RIGHT_HOLD,
    WINGS_RIGHT_IN,
    WINGS_RIGHT_OUT,
    WINGS_RIGHT_TOGGLE
};
} // namespace user
} // namespace wisco

#endif