#ifndef PROS_ADAPTER_PROS_HEADING_HPP
#define PROS_ADAPTER_PROS_HEADING_HPP

#include <memory>

#include "pros/distance.hpp"
#include "wisco/io/IDistanceSensor.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{
/**
 * @brief Pros distance sensor adapter for the wisco IDistanceSensor interface
 * @author Nathan Sandvig
 * 
 */
class ProsDistance : public wisco::io::IDistanceSensor
{
private:
    /**
     * @brief Converts the units for the sensor
     * 
     */
    static constexpr double UNIT_CONVERTER{1.0 / 25.4};
    
    /**
     * @brief The sensor being adapted
     * 
     */
    std::unique_ptr<pros::Distance> m_sensor{};

    /**
     * @brief The tuning constant for the sensor
     * 
     */
    double m_tuning_constant{1};

    /**
     * @brief The tuning offset for the sensor
     * 
     */
    double m_tuning_offset{};

public:
    /**
     * @brief Construct a new Pros Heading object
     * 
     * @param sensor The sensor being adapted
     * @param tuning_constant The tuning constant multiplier for the sensor
     * @param tuning_offset The tuning offset for the sensor
     */
    ProsDistance(std::unique_ptr<pros::Distance>& sensor, double tuning_constant = 1, double tuning_offset = 0);

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
     * @brief Get the distance of the sensor in inches
     * 
     * @return double The rotation in inches
     */
    double getDistance() override;
};
} // namespace pros_adapters

#endif