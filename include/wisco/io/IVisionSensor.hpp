#ifndef WISCO_IO_I_VISION_SENSOR_HPP
#define WISCO_IO_I_VISION_SENSOR_HPP

#include <vector>

#include "VisionObject.hpp"

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
 * @brief Interface for a vision sensor
 * @author Nathan Sandvig
 * 
 */
class IVisionSensor
{
public:
    /**
     * @brief Destroy the IVisionSensor object
     * 
     */
    virtual ~IVisionSensor() = default;

    /**
     * @brief Initializes the sensor
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Get the objects the vision sensor can see
     * 
     * @return std::vector<VisionObject> The objects the vision sensor can see
     */
    virtual std::vector<VisionObject> getObjects() = 0;
};
} // namespace io
} // namespace wisco

#endif