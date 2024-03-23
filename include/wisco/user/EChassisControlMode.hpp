#ifndef WISCO_USER_E_CHASSIS_CONTROL_MODE_HPP
#define WISCO_USER_E_CHASSIS_CONTROL_MODE_HPP

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
 * @brief Defines all different chassis control formats
 * @author Nathan Sandvig
 * 
 */
enum class EChassisControlMode
{
    SINGLE_ARCADE_LEFT,
    SINGLE_ARCADE_RIGHT,
    SPLIT_ARCADE_LEFT,
    SPLIT_ARCADE_RIGHT,
    TANK
};
} // namespace user
} // namespace wisco

#endif