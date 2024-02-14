#ifndef PROS_ADAPTERS_PROS_ROTATION_HPP
#define PROS_ADAPTERS_PROS_ROTATION_HPP

#include <cmath>
#include <memory>

#include "pros/rotation.hpp"
#include "wisco/sensors/IRotationSensor.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros rotation sensor adapter for the wisco IRotationSensor interface
 * @author Nathan Sandvig
 * 
 */
class ProsRotation : public wisco::sensors::IRotationSensor
{
private:
    /**
     * @brief Conversion factor for the input and outputs units
     * 
     */
    static constexpr double UNIT_CONVERSION{18000 / M_PI};

    /**
     * @brief The rotation sensor being adapted
     * 
     */
    std::unique_ptr<pros::Rotation> m_sensor{};

public:
    /**
     * @brief Construct a new Pros Rotation object
     * 
     * @param sensor The sensor to adapt
     */
    ProsRotation(std::unique_ptr<pros::Rotation>& sensor);

    /**
     * @brief Initializes the rotation sensor
     * 
     */
    void initialize() override;

    /**
     * @brief Resets the rotation sensor
     * 
     */
    void reset() override;

    /**
     * @brief Get the rotation of the sensor in radians
     * 
     * @return double The number of radians of rotation
     */
    double getRotation() override;

    /**
     * @brief Set the rotation of the sensor in radians
     * 
     * @param rotation The number of radians of rotation
     */
    void setRotation(double rotation) override;

    /**
     * @brief Get the angle of the sensor in radians
     * 
     * @return double The angle in radians
     */
    double getAngle() override;
};
}

#endif