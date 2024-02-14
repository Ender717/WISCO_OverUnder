#ifndef PROS_ADAPTERS_PROS_TASK_HPP
#define PROS_ADAPTERS_PROS_TASK_HPP

#include <memory>

#include "pros/rtos.hpp"
#include "wisco/rtos/ITask.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros rtos task adapter for the wisco rtos ITask interface
 * @author Nathan Sandvig
 * 
 */
class ProsTask : public wisco::rtos::ITask
{
private:
    /**
     * @brief The pros task being adapted
     * 
     */
    std::unique_ptr<pros::Task> task{};

public:
    /**
     * @brief Starts the task
     * 
     * @param function The function to run in the task
     * @param parameters The parameters for the function
     */
    void start(void (*function)(void*), void* parameters) override;

    /**
     * @brief Removes the task from the system
     * 
     */
    void remove() override;

    /**
     * @brief Suspends the task in the scheduler
     * 
     */
    void suspend() override;

    /**
     * @brief Resumes the task in the scheduler
     * 
     */
    void resume() override;

    /**
     * @brief Waits for the task to finish
     * 
     */
    void join() override;
};
} // namespace pros_adapters

#endif