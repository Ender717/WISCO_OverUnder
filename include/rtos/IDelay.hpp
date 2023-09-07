#ifndef RTOS_I_DELAY_HPP
#define RTOS_I_DELAY_HPP

#include <cstdint>

namespace rtos
{
/**
 * @brief An interface for rtos delays
 *
 * @author Nathan Sandvig
 */
class IDelay
{
public:
    /**
     * @brief Destroy the IDelay object
     *
     */
    virtual ~IDelay() = default;

    /**
     * @brief Delays the rtos for an input number of milliseconds
     *
     * @param milliseconds The number of milliseconds to delay
     */
    virtual void delayMS(uint32_t milliseconds) = 0;

    /**
     * @brief Delays the rtos for an input number of microseconds
     *
     * @param microseconds The number of microseconds to delay
     */
    virtual void delayUS(uint32_t microseconds) = 0;
};
} // namespace rtos

#endif