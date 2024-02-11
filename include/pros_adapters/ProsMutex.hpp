#ifndef PROS_ADAPTERS_PROS_MUTEX_HPP
#define PROS_ADAPTERS_PROS_MUTEX_HPP

#include <memory>

#include "pros/rtos.hpp"
#include "wisco/rtos/IMutex.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros rtos mutex adapter for the wisco rtos IMutex interface
 * @author Nathan Sandvig
 * 
 */
class ProsMutex : public wisco::rtos::IMutex
{
private:
    /**
     * @brief The mutex being adapted
     * 
     */
    std::unique_ptr<pros::Mutex> m_mutex{};

public:
    /**
     * @brief Construct a new Pros Mutex object
     * 
     * @param mutex The mutex to adapt
     */
    ProsMutex(std::unique_ptr<pros::Mutex>& mutex);

    /**
     * @brief Takes and locks the mutex
     * 
     */
    void take() override;

    /**
     * @brief Gives and unlocks the mutex
     * 
     */
    void give() override;
};
}

#endif