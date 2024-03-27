#ifndef WISCO_IO_I_DISTANCE_SENSOR_HPP
#define WISCO_IO_I_DISTANCE_SENSOR_HPP

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
 * @brief Interface for distance tracking sensors
 * @author Nathan Sandvig
 * 
 */
class IDistanceSensor
{
public:
    /**
     * @brief Destroy the IDistanceSensor object
     * 
     */
    virtual ~IDistanceSensor() = default;

    /**
     * @brief Initializes the sensor
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Resets the sensor
     * 
     */
    virtual void reset() = 0;

    /**
     * @brief Get the distance detected by the sensor in inches
     * 
     * @return double The distance detected by the sensor
     */
    virtual double getDistance() = 0;
};
} // namespace io
} // namespace wisco

#endif