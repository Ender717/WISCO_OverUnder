#ifndef WISCO_IO_I_BOOLEAN_SENSOR_HPP
#define WISCO_IO_I_BOOLEAN_SENSOR_HPP

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
 * @brief Interface for sensors that generate a boolean value
 * @author Nathan Sandvig
 * 
 */
class IBooleanSensor
{
public:
    /**
     * @brief Destroy the IBooleanSensor object
     * 
     */
    virtual ~IBooleanSensor() = default;

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
     * @brief Get the boolean value of the sensor
     * 
     * @return bool The value of the sensor
     */
    virtual bool getValue() = 0;
};
} // namespace io
} // namespace wisco

#endif