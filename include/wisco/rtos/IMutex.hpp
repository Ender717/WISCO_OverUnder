#ifndef WISCO_RTOS_I_MUTEX_HPP
#define WISCO_RTOS_I_MUTEX_HPP

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
 * @brief Interface for rtos mutexes
 * @author Nathan Sandvig
 * 
 */
class IMutex
{
public:
    /**
     * @brief Destroy the IMutex object
     * 
     */
    virtual ~IMutex() = default;

    /**
     * @brief Takes the mutex and locks it
     * 
     */
    virtual void take() = 0;

    /**
     * @brief Gives the mutex and unlocks it
     * 
     */
    virtual void give() = 0;
};

}
}

#endif