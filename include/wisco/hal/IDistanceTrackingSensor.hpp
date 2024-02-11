#ifndef WISCO_HAL_I_DISTANCE_TRACKING_SENSOR_HPP
#define WISCO_HAL_I_DISTANCE_TRACKING_SENSOR_HPP

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for the hardware abstraction layer interfaces
 * @author Nathan Sandvig
 * 
 */
namespace hal
{
/**
 * @brief Interface for distance tracking sensors
 * @author Nathan Sandvig
 * 
 */
class IDistanceTrackingSensor
{
public:
    /**
     * @brief Destroy the IDistanceTrackingSensor object
     * 
     */
    virtual ~IDistanceTrackingSensor() = default;

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
     * @brief Get the distance tracked by the sensor in inches
     * 
     * @return double The distance tracked by the sensor
     */
    virtual double getDistance() = 0;

    /**
     * @brief Set the distance tracked by the sensor in inches
     * 
     * @param distance The new distance tracked value
     */
    virtual void setDistance(double distance) = 0;
};
} // namespace hal
} // namespace wisco

#endif