#ifndef WISCO_USER_UMBRELLA_E_UMBRELLA_CONTROL_MODE_HPP
#define WISCO_USER_UMBRELLA_E_UMBRELLA_CONTROL_MODE_HPP

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
 * @brief Namespace for all umbrella user control components
 * @author Nathan Sandvig
 * 
 */
namespace umbrella
{

/**
 * @brief Defines all different umbrella control formats
 * @author Nathan Sandvig
 * 
 */
enum class EUmbrellaControlMode
{
    HOLD,
    SINGLE_TOGGLE,
    SPLIT_TOGGLE
};
} // namespace umbrella
} // namespace user
} // namespace wisco

#endif