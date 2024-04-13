#ifndef WISCO_USER_E_CONTROL_TYPE_HPP
#define WISCO_USER_E_CONTROL_TYPE_HPP

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
 * @brief Defines all different control types
 * @author Nathan Sandvig
 * 
 */
enum class EControlType
{
    DRIVE,
    ELEVATOR,
    HANG,
    INTAKE,
    LOADER,
    WINGS
};
} // namespace user
} // namespace wisco

#endif