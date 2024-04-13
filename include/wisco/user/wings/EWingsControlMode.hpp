#ifndef WISCO_USER_WINGS_E_WINGS_CONTROL_MODE_HPP
#define WISCO_USER_WINGS_E_WINGS_CONTROL_MODE_HPP

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
 * @brief Namespace for all wings user control components
 * @author Nathan Sandvig
 * 
 */
namespace wings
{

/**
 * @brief Defines all different wings control formats
 * @author Nathan Sandvig
 * 
 */
enum class EWingsControlMode
{
    DUAL_HOLD,
    DUAL_SPLIT,
    DUAL_TOGGLE,
    SINGLE_HOLD,
    SINGLE_SPLIT,
    SINGLE_TOGGLE
};
} // namespace wings
} // namespace user
} // namespace wisco

#endif