#ifndef HAL_RTOS_DELAY_HPP
#define HAL_RTOS_DELAY_HPP

#include <cstdint>

#include "pros/rtos.hpp"

/**
 * @brief Namespace for the hardware abstraction layer
 * @author Nathan Sandvig
 *
 */
namespace hal
{

/**
 * @brief Namespace for the real time embedded system functionality
 * @author Nathan Sandvig
 *
 */
namespace rtos
{

/**
 * @brief Delays the active task for an input number of milliseconds
 *
 * @param millis The number of milliseconds to delay
 */
void delay(const uint32_t millis);

} // namespace rtos
} // namespace hal

#endif