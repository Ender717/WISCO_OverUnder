#ifndef PROS_ADAPTER_PROS_HEADING_HPP
#define PROS_ADAPTER_PROS_HEADING_HPP

#include <cmath>
#include <memory>

#include "pros/imu.hpp"
#include "wisco/io/IHeadingSensor.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{
/**
 * @brief Pros inertial sensor adapter for the wisco IHeadingSensor interface
 * @author Nathan Sandvig
 * 
 */
class ProsHeading : public wisco::io::IHeadingSensor
{
private:
    /**
     * @brief Converts the units for the sensor
     * 
     */
    static constexpr double UNIT_CONVERTER{-180 / M_PI};
    
    /**
     * @brief The sensor being adapted
     * 
     */
    std::unique_ptr<pros::Imu> m_sensor{};

    /**
     * @brief The tuning constant for the sensor
     * 
     */
    double m_tuning_constant{1};

public:
    /**
     * @brief Construct a new Pros Heading object
     * 
     * @param sensor The sensor being adapted
     * @param tuning_constant The tuning constant multiplier for the sensor
     */
    ProsHeading(std::unique_ptr<pros::Imu>& sensor, double tuning_constant = 1);

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
     * @brief Get the heading of the sensor in radians
     * 
     * @return double The heading in radians
     */
    double getHeading() override;

    /**
     * @brief Set the heading of the sensor in radians
     * 
     * @param heading The heading in radians
     */
    void setHeading(double heading) override;

    /**
     * @brief Get the rotation of the sensor in radians
     * 
     * @return double The rotation in radians
     */
    double getRotation() override;

    /**
     * @brief Set the rotation of the sensor in radians
     * 
     * @param rotation The rotation in radians
     */
    void setRotation(double rotation) override;
};
} // namespace pros_adapters

#endif