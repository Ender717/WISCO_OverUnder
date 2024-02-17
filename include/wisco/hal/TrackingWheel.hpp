#ifndef WISCO_ROBOT_HAL_TRACKING_WHEEL_HPP
#define WISCO_ROBOT_HAL_TRACKING_WHEEL_HPP

#include <memory>

#include "wisco/io/IDistanceTrackingSensor.hpp"
#include "wisco/io/IRotationSensor.hpp"

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
 * @brief A tracking wheel sensor
 * @author Nathan Sandvig
 * 
 */
class TrackingWheel : public io::IDistanceTrackingSensor
{
private:
    /**
     * @brief The sensor on the tracking wheel
     * 
     */
    std::unique_ptr<io::IRotationSensor> m_sensor{};

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
    TrackingWheel(std::unique_ptr<io::IRotationSensor>& sensor, double wheel_radius);

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