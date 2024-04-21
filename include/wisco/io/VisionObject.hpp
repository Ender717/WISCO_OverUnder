#ifndef WISCO_IO_VISION_OBJECT_HPP
#define WISCO_IO_VISION_OBJECT_HPP

#include "EVisionObjectID.hpp"

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
 * @brief A vision object with units in radians relative to the vision sensor
 * @author Nathan Sandvig
 * 
 */
struct VisionObject
{
    /**
     * @brief The id of the object
     * 
     */
    EVisionObjectID id{EVisionObjectID::UNKNOWN};

    /**
     * @brief The horizontal heading of the object
     * 
     */
    double horizontal{};

    /**
     * @brief The vertical heading of the object
     * 
     */
    double vertical{};

    /**
     * @brief The width of the object
     * 
     */
    double width{};

    /**
     * @brief The height of the object
     * 
     */
    double height{};
};
} // namespace io
} // namespace wisco

#endif