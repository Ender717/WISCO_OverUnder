#ifndef WISCO_CONTROL_MOTION_E_TURN_DIRECTION_HPP
#define WISCO_CONTROL_MOTION_E_TURN_DIRECTION_HPP

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for control algorithms
 * @author Nathan Sandvig
 * 
 */
namespace control
{

/**
 * @brief Namespace for basic motion controls
 * @author Nathan Sandvig
 * 
 */
namespace motion
{

/**
 * @brief Enum for turn directions
 * @author Nathan Sandvig
 * 
 */
enum class ETurnDirection
{
    AUTO,
    CLOCKWISE,
    COUNTERCLOCKWISE
};
} // namespace motion
} // namespace control
} // namespace wisco

#endif