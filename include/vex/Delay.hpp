#ifndef VEX_DELAY_HPP
#define VEX_DELAY_HPP

#include "pros/rtos.hpp"

#include "rtos/IDelay.hpp"

namespace vex
{
/**
 * @brief The platform-specific implementation of RTOS delays for vex
 *
 * @author Nathan Sandvig
 */
class Delay : public rtos::IDelay
{
private:
    /**
     * @brief The number of microseconds in a millisecond
     *
     */
    static constexpr uint16_t US_PER_MS{1000};

public:
    /**
     * @brief Delays the rtos for an input number of milliseconds
     *
     * @param milliseconds The number of milliseconds to delay
     */
    void delayMS(uint32_t milliseconds) final;

    /**
     * @brief Delays the rtos for an input number of microseconds
     *
     * @param microseconds The number of microseconds to delay
     */
    void delayUS(uint32_t microseconds) final;
};
} // namespace vex

#endif