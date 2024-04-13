#ifndef WISCO_USER_HANG_E_HANG_CONTROL_MODE_HPP
#define WISCO_USER_HANG_E_HANG_CONTROL_MODE_HPP

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
 * @brief Namespace for all hang user control components
 * @author Nathan Sandvig
 * 
 */
namespace hang
{

/**
 * @brief Defines all different hang control formats
 * @author Nathan Sandvig
 * 
 */
enum class EHangControlMode
{
    PRESET_SPLIT,
    PRESET_TOGGLE_SINGLE,
    PRESET_TOGGLE_LADDER,
    PRESET_TOGGLE_RESET
};
} // namespace hang
} // namespace user
} // namespace wisco

#endif