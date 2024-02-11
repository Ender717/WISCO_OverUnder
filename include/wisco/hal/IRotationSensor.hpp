#ifndef WISCO_HAL_I_ROTATION_SENSOR_HPP
#define WISCO_HAL_I_ROTATION_SENSOR_HPP

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
 * @brief Interface for rotation sensors
 * @author Nathan Sandvig
 * 
 */
class IRotationSensor
{
public:
    /**
     * @brief Destroy the IRotationSensor object
     * 
     */
    virtual ~IRotationSensor() = default;

    /**
     * @brief Initializes the rotation sensor
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Resets the rotation sensor
     * 
     */
    virtual void reset() = 0;

    /**
     * @brief Get the rotation of the sensor in radians
     * 
     * @return double The number of radians of rotation
     */
    virtual double getRotation() = 0;

    /**
     * @brief Set the rotation of the sensor in radians
     * 
     * @param rotation The number of radians of rotation
     */
    virtual void setRotation(double rotation) = 0;

    /**
     * @brief Get the angle of the sensor in radians
     * 
     * @return double The angle in radians
     */
    virtual double getAngle() = 0;
};
}
}

#endif