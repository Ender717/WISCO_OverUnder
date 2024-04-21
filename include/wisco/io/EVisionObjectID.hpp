#ifndef WISCO_IO_E_VISION_TARGET_HPP
#define WISCO_IO_E_VISION_TARGET_HPP

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
    
/**
 * @brief Namespace for the io types
 * @author Nathan Sandvig
 * 
 */
namespace io
{

/**
 * @brief The recognizable vision objects
 * @author Nathan Sandvig
 * 
 */
enum class EVisionObjectID
{
    BLUE_TRIBALL,
    GREEN_TRIBALL,
    RED_TRIBALL,
    UNKNOWN
};
} // namespace io
} // namespace wisco

#endif