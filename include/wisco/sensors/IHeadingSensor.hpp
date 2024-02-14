#ifndef WISCO_SENSORS_I_HEADING_SENSOR_HPP
#define WISCO_SENSORS_I_HEADING_SENSOR_HPP

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for the sensor types
 * @author Nathan Sandvig
 * 
 */
namespace sensors
{
/**
 * @brief Interface for heading sensors
 * @author Nathan Sandvig
 * 
 */
class IHeadingSensor
{
public:
    /**
     * @brief Destroy the IHeadingSensor object
     * 
     */
    virtual ~IHeadingSensor() = default;

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
     * @brief Get the heading of the sensor in radians
     * 
     * @return double The heading in radians
     */
    virtual double getHeading() = 0;

    /**
     * @brief Set the heading of the sensor in radians
     * 
     * @param heading The heading in radians
     */
    virtual void setHeading(double heading) = 0;

    /**
     * @brief Get the rotation of the sensor in radians
     * 
     * @return double The rotation in radians
     */
    virtual double getRotation() = 0;

    /**
     * @brief Set the rotation of the sensor in radians
     * 
     * @param rotation The rotation in radians
     */
    virtual void setRotation(double rotation) = 0;
};
} // namespace sensors
} // namespace wisco

#endif