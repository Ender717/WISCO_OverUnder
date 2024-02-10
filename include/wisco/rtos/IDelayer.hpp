#ifndef WISCO_RTOS_I_DELAYER_HPP
#define WISCO_RTOS_I_DELAYER_HPP

#include <cstdint>

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
     * @brief Delays the rtos system for a number of milliseconds
     * 
     * @param millis The number of milliseconds to delay
     */
    virtual void delay(uint32_t millis);
};
}
}

#endif