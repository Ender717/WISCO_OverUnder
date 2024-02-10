#ifndef PROS_ADAPTERS_PROS_DELAYER_HPP
#define PROS_ADAPTERS_PROS_DELAYER_HPP

#include "pros/rtos.hpp"
#include "wisco/rtos/IDelayer.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros rtos delay adapter for the wisco rtos IDelayer interface
 * @author Nathan Sandvig
 * 
 */
class ProsDelayer : public wisco::rtos::IDelayer
{
public:
    /**
     * @brief Delays the rtos system for a number of milliseconds
     * 
     * @param millis The number of milliseconds to delay
     */
    void delay(uint32_t millis) override;
};
}

#endif