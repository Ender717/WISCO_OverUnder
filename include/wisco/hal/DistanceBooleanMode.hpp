#ifndef WISCO_HAL_DISTANCE_BOOLEAN_MODE_HPP
#define WISCO_HAL_DISTANCE_BOOLEAN_MODE_HPP

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief The namespace for the hardware abstraction layer
 * @author Nathan Sandvig
 *
 */
namespace hal
{

/**
 * @brief The modes of a distance boolean sensor
 * @author Nathan Sandvig
 * 
 */
enum class DistanceBooleanMode
{
    ABOVE_THRESHOLD,
    BELOW_THRESHOLD,
    BETWEEN_THRESHOLD
};
} // namespace hal
} // namespace wisco

#endif