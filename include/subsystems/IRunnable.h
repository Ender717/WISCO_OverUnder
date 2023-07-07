#ifndef I_RUNNABLE_H
#define I_RUNNABLE_H

namespace subsystems
{
/**
 * @brief An interface for subsystems that can be run in the background
 *
 * @author Nathan Sandvig
 */
class IRunnable
{
public:
    /**
     * @brief Destroy the IRunnable object
     *
     */
    virtual ~IRunnable() = default;

    /**
     * @brief Run the runnable object
     *
     */
    virtual void run() = 0;
};
} // namespace subsystems

#endif