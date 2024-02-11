#ifndef WISCO_ROBOT_SENSORS_TRACKING_WHEEL_HPP
#define WISCO_ROBOT_SENSORS_TRACKING_WHEEL_HPP

#include <memory>

#include "wisco/hal/IDistanceTrackingSensor.hpp"
#include "wisco/hal/IRotationSensor.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief The namespace that holds all custom sensors
 * @author Nathan Sandvig
 *
 */
namespace sensors
{
/**
 * @brief A tracking wheel sensor
 * @author Nathan Sandvig
 * 
 */
class TrackingWheel : public hal::IDistanceTrackingSensor
{
private:
    /**
     * @brief The sensor on the tracking wheel
     * 
     */
    std::unique_ptr<hal::IRotationSensor> m_sensor{};

    /**
     * @brief The radius of the wheel in inches
     * 
     */
    double m_wheel_radius{};

public:
    /**
     * @brief Construct a new Tracking Wheel object
     * 
     * @param sensor The rotation sensor on the tracking wheel
     * @param wheel_radius The radius of the tracking wheel in inches
     */
    TrackingWheel(std::unique_ptr<hal::IRotationSensor>& sensor, double wheel_radius);

    /**
     * @brief Initializes the sensor
     * 
     */
    void initialize() override;

    /**
     * @brief Resets the sensor
     * 
     */
    void reset() override;

    /**
     * @brief Get the distance tracked by the sensor in inches
     * 
     * @return double The distance tracked by the sensor
     */
    double getDistance() override;

    /**
     * @brief Set the distance tracked by the sensor in inches
     * 
     * @param distance The new distance tracked value
     */
    void setDistance(double distance) override;
};
} // namespace sensors
} // namespace wisco

#endif