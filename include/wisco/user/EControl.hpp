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
    ELEVATOR_IN,
    ELEVATOR_FIELD,
    ELEVATOR_MATCH_LOAD,
    ELEVATOR_OUT,
    ELEVATOR_TOGGLE,
    INTAKE_IN,
    INTAKE_OUT,
    INTAKE_TOGGLE
};
} // namespace user
} // namespace wisco

#endif