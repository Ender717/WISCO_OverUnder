#ifndef PROS_ADAPTERS_PROS_PISTON_HPP
#define PROS_ADAPTERS_PROS_PISTON_HPP

#include <memory>

#include "pros/adi.hpp"

#include "wisco/io/IPiston.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros piston adapter for the wisco IPiston interface
 * @author Nathan Sandvig
 * 
 */
class ProsPiston : public wisco::io::IPiston
{
private:
    /**
     * @brief The digital output for the piston
     * 
     */
    std::unique_ptr<pros::adi::DigitalOut> m_digital_out{};

    /**
     * @brief The value to use for extended
     * 
     */
    bool m_extended_value{};

    /**
     * @brief Whether the piston is currently extended or not
     * 
     */
    bool extended{};

public:
    /**
     * @brief Construct a new Pros Piston object
     * 
     * @param digital_out The digital output for the piston
     * @param extended_value The value to use for extended
     */
    ProsPiston(std::unique_ptr<pros::adi::DigitalOut>& digital_out, bool extended_value = true);

    /**
     * @brief Extends the piston
     * 
     */
    void extend() override;

    /**
     * @brief Retracts the piston
     * 
     */
    void retract() override;

    /**
     * @brief Toggles the piston state
     * 
     */
    void toggle() override;

    /**
     * @brief Checks if the piston is extended
     * 
     * @return true The piston is extended
     * @return false The piston is not extended
     */
    bool isExtended() override;

    /**
     * @brief Checks if the piston is retracted
     * 
     * @return true The piston is retracted
     * @return false The piston is not retracted
     */
    bool isRetracted() override;
};
} // namespace pros_adapters

#endif