#ifndef WISCO_HAL_DISTANCE_BOOLEAN_SENSOR_HPP
#define WISCO_HAL_DISTANCE_BOOLEAN_SENSOR_HPP

#include <memory>

#include "wisco/io/IDistanceSensor.hpp"
#include "wisco/io/IBooleanSensor.hpp"

#include "DistanceBooleanMode.hpp"

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
 * @brief A distance sensor used to create boolean outputs
 * @author Nathan Sandvig
 * 
 */
class DistanceBooleanSensor : public io::IBooleanSensor
{
private:
    /**
     * @brief The distance sensor
     * 
     */
    std::unique_ptr<io::IDistanceSensor> m_distance_sensor{};

    /**
     * @brief The mode of the sensor
     * 
     */
    DistanceBooleanMode m_mode{};

    /**
     * @brief The lower threshold of the sensor
     * 
     */
    double m_lower_threshold{};

    /**
     * @brief The upper threshold of the sensor
     * 
     */
    double m_upper_threshold{};

    /**
     * @brief The current boolean value
     * 
     */
    bool value{};

public:
    /**
     * @brief Construct a new Distance Boolean Sensor object
     * 
     * @param distance_sensor The distance sensor
     * @param mode The mode of the sensor
     * @param lower_threshold The lower threshold of the sensor
     */
    DistanceBooleanSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor, 
                          DistanceBooleanMode mode,
                          double lower_threshold);
    
    /**
     * @brief Construct a new Distance Boolean Sensor object
     * 
     * @param distance_sensor The distance sensor
     * @param mode The mode of the sensor
     * @param lower_threshold The lower threshold of the sensor
     * @param upper_threshold The upper threshold of the sensor
     */
    DistanceBooleanSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor, 
                          DistanceBooleanMode mode,
                          double lower_threshold,
                          double upper_threshold);

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
} // namespace hal
} // namespace wisco

#endif