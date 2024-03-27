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
     * @brief Clones the IDelayer object
     * 
     * @return std::unique_ptr<IDelayer> The cloned IDelayer object
     */
    std::unique_ptr<wisco::rtos::IDelayer> clone() const override;

    /**
     * @brief Delays the rtos system for a number of milliseconds
     * 
     * @param millis The number of milliseconds to delay
     */
    void delay(uint32_t millis) override;

    /**
     * @brief Delays the rtos system until a certain system time in milliseconds
     * 
     * @param time The time in milliseconds to delay until
     */
    void delayUntil(uint32_t time) override;
};
}

#endif