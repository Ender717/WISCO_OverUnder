#ifndef WISCO_USER_INTAKE_E_INTAKE_CONTROL_MODE_HPP
#define WISCO_USER_INTAKE_E_INTAKE_CONTROL_MODE_HPP

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
 * @brief Namespace for all intake user control components
 * @author Nathan Sandvig
 * 
 */
namespace intake
{

/**
 * @brief Defines all different intake control formats
 * @author Nathan Sandvig
 * 
 */
enum class EIntakeControlMode
{
    SINGLE_TOGGLE,
    SPLIT_HOLD,
    SPLIT_TOGGLE
};
} // namespace intake
} // namespace user
} // namespace wisco

#endif