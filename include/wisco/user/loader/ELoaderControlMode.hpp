#ifndef WISCO_USER_LOADER_E_LOADER_CONTROL_MODE_HPP
#define WISCO_USER_LOADER_E_LOADER_CONTROL_MODE_HPP

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
 * @brief Namespace for all loader user control components
 * @author Nathan Sandvig
 * 
 */
namespace loader
{

/**
 * @brief Defines all different loader control formats
 * @author Nathan Sandvig
 * 
 */
enum class ELoaderControlMode
{
    HOLD,
    MACRO,
    SINGLE_TOGGLE,
    SPLIT_TOGGLE
};
} // namespace loader
} // namespace user
} // namespace wisco

#endif