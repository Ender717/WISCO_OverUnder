#ifndef WISCO_RTOS_I_DELAYER_HPP
#define WISCO_RTOS_I_DELAYER_HPP

#include <cstdint>
#include <memory>

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for the rtos interface of the library
 * @author Nathan Sandvig
 * 
 */
namespace rtos
{

/**
 * @brief Interface for rtos delay systems
 * @author Nathan Sandvig
 * 
 */
class IDelayer
{
public:
    /**
     * @brief Destroy the IDelayer object
     * 
     */
    virtual ~IDelayer() = default;

    /**
     * @brief Clones the IDelayer object
     * 
     * @return std::unique_ptr<IDelayer> The cloned IDelayer object
     */
    virtual std::unique_ptr<wisco::rtos::IDelayer> clone() const = 0;

    /**
     * @brief Delays the rtos system for a number of milliseconds
     * 
     * @param millis The number of milliseconds to delay
     */
    virtual void delay(uint32_t millis) = 0;

    /**
     * @brief Delays the rtos system until a certain system time in milliseconds
     * 
     * @param time The time in milliseconds to delay until
     */
    virtual void delayUntil(uint32_t time) = 0;
};
}
}

#endif