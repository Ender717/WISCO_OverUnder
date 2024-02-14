#ifndef WISCO_RTOS_I_CLOCK_HPP
#define WISCO_RTOS_I_CLOCK_HPP

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
 * @brief Interface for an rtos system clock
 * @author Nathan Sandvig
 * 
 */
class IClock
{
public:
    /**
     * @brief Destroy the IClock object
     * 
     */
    virtual ~IClock() = default;

    /**
     * @brief Get the clock time in milliseconds
     * 
     * @return uint32_t The clock time in milliseconds
     */
    virtual uint32_t getTime() = 0;
};
} // namespace rtos
} // namespace wisco

#endif