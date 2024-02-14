#ifndef WISCO_RTOS_I_TASK_HPP
#define WISCO_RTOS_I_TASK_HPP

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
 * @brief Interface for an rtos task system
 * @author Nathan Sandvig
 * 
 */
class ITask
{
public:
    /**
     * @brief Destroy the ITask object
     * 
     */
    virtual ~ITask() = default;

    /**
     * @brief Starts the task
     * 
     * @param function The function to run in the task
     * @param parameters The parameters for the function
     */
    virtual void start(void (*function)(void*) , void* parameters) = 0;

    /**
     * @brief Removes the task from the system
     * 
     */
    virtual void remove() = 0;

    /**
     * @brief Suspends the task in the scheduler
     * 
     */
    virtual void suspend() = 0;

    /**
     * @brief Resumes the task in the scheduler
     * 
     */
    virtual void resume() = 0;

    /**
     * @brief Waits for the task to finish
     * 
     */
    virtual void join() = 0;
};

} // namespace rtos
} // namespace wisco

#endif