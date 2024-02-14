#ifndef PROS_ADAPTERS_PROS_CLOCK_HPP
#define PROS_ADAPTERS_PROS_CLOCK_HPP

#include "pros/rtos.hpp"

#include "wisco/rtos/IClock.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros rtos clock adapter for the wisco rtos IClock interface
 * @author Nathan Sandvig
 * 
 */
class ProsClock : public wisco::rtos::IClock
{
public:
    /**
     * @brief Get the system clock time in milliseconds
     * 
     * @return uint32_t The system clock time in milliseconds
     */
    uint32_t getTime() override;
};
} // namespace pros_adapters

#endif