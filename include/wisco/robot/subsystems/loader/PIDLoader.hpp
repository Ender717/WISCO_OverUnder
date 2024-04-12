#ifndef WISCO_ROBOT_SUBSYSTEMS_LOADER_PID_LOADER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_LOADER_PID_LOADER_HPP

#include <memory>

#include "wisco/control/PID.hpp"
#include "wisco/hal/MotorGroup.hpp"
#include "wisco/rtos/IClock.hpp"
#include "wisco/rtos/IDelayer.hpp"
#include "wisco/rtos/IMutex.hpp"
#include "wisco/rtos/ITask.hpp"

#include "ILoader.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief The namespace that holds all robot classes
 * @author Nathan Sandvig
 *
 */
namespace robot
{

/**
 * @brief Namespace for all robot subsystems
 * @author Nathan Sandvig
 * 
 */
namespace subsystems
{

/**
 * @brief Namespace for loader classes
 * @author Nathan Sandvig
 * 
 */
namespace loader
{

/**
 * @brief An loader controller with PID position control
 * @author Nathan Sandvig
 * 
 */
class PIDLoader : public ILoader
{
private:
    /**
     * @brief The loop delay on the task
     * 
     */
    static constexpr uint8_t TASK_DELAY{10};

    /**
     * @brief The task loop function for background updates
     * 
     * @param params 
     */
    static void taskLoop(void* params);

    /**
     * @brief The rtos clock
     * 
     */
    std::unique_ptr<rtos::IClock> m_clock{};

    /**
     * @brief The rtos delayer
     * 
     */
    std::unique_ptr<rtos::IDelayer> m_delayer{};

    /**
     * @brief The mutex for thread safety
     * 
     */
    std::unique_ptr<rtos::IMutex> m_mutex{};

    /**
     * @brief The background task handler
     * 
     */
    std::unique_ptr<rtos::ITask> m_task{};

    /**
     * @brief The position PID controller
     * 
     */
    control::PID m_pid{};

    /**
     * @brief The motors on the loader
     * 
     */
    hal::MotorGroup m_motors{};

    /**
     * @brief The position for match loads
     * 
     */
    double m_match_load_position{};

    /**
     * @brief The position for ready
     * 
     */
    double m_ready_position{};

    /**
     * @brief The allowed tolerance around the target positions
     * 
     */
    double m_position_tolerance{};

    /**
     * @brief The position setting of the loader
     * 
     */
    double target_position{};

    /**
     * @brief Runs all the object-specific updates in the task loop
     * 
     */
    void taskUpdate();

    /**
     * @brief Updates the system state
     * 
     */
    void updateState();

    /**
     * @brief Updates the loader position
     * 
     */
    void updatePosition();

public:
    /**
     * @brief Initializes the loader
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the loader
     * 
     */
    void run() override;

    /**
     * @brief Does one match load
     * 
     */
    void doMatchLoad() override;

    /**
     * @brief Checks if the match load is loaded
     * 
     * @return true The match load is loaded
     * @return false The match load is not loaded
     */
    bool isLoaded() override;

    /**
     * @brief Checks if the loader is ready
     * 
     * @return true The loader is ready
     * @return false The loader is not ready
     */
    bool isReady() override;

    /**
     * @brief Set the rtos clock
     * 
     * @param clock The rtos clock
     */
    void setClock(const std::unique_ptr<rtos::IClock>& clock);

    /**
     * @brief Set the rtos delayer
     * 
     * @param delayer The rtos delayer
     */
    void setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer);

    /**
     * @brief Set the thread mutex
     * 
     * @param mutex The thread mutex
     */
    void setMutex(std::unique_ptr<rtos::IMutex>& mutex);

    /**
     * @brief Set the task handler
     * 
     * @param task The task handler
     */
    void setTask(std::unique_ptr<rtos::ITask>& task);

    /**
     * @brief Set the PID controller
     * 
     * @param pid The PID controller
     */
    void setPID(control::PID pid);

    /**
     * @brief Set the motors
     * 
     * @param motors The motors
     */
    void setMotors(hal::MotorGroup& motors);

    /**
     * @brief Sets the position for match loads
     * 
     * @param match_load_position The position for match loads
     */
    void setMatchLoadPosition(double match_load_position);

    /**
     * @brief Set the position for ready
     * 
     * @param ready_position The position for ready
     */
    void setReadyPosition(double ready_position);

    /**
     * @brief Set the allowed tolerance around the target positions
     * 
     * @param position_tolerance The allowed tolerance around the target positions
     */
    void setPositionTolerance(double position_tolerance);
};
} // namespace loader
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif