#ifndef WISCO_ROBOT_SUBSYSTEMS_INTAKE_PID_INTAKE_HPP
#define WISCO_ROBOT_SUBSYSTEMS_INTAKE_PID_INTAKE_HPP

#include <memory>

#include "wisco/control/PID.hpp"
#include "wisco/hal/MotorGroup.hpp"
#include "wisco/rtos/IClock.hpp"
#include "wisco/rtos/IDelayer.hpp"
#include "wisco/rtos/IMutex.hpp"
#include "wisco/rtos/ITask.hpp"

#include "IIntake.hpp"

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
 * @brief Namespace for intake classes
 * @author Nathan Sandvig
 * 
 */
namespace intake
{

/**
 * @brief An intake controller with PID velocity control
 * @author Nathan Sandvig
 * 
 */
class PIDIntake : public IIntake
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
     * @brief The velocity PID controller
     * 
     */
    control::PID m_pid{};

    /**
     * @brief The motors on the intake
     * 
     */
    hal::MotorGroup m_motors{};

    /**
     * @brief The radius of the intake roller
     * 
     */
    double m_roller_radius{};

    /**
     * @brief The velocity setting of the intake
     * 
     */
    double m_velocity{};

    /**
     * @brief Whether or not to control with velocity
     * 
     */
    bool velocity_control{};

    /**
     * @brief Runs all the object-specific updates in the task loop
     * 
     */
    void taskUpdate();

    /**
     * @brief Updates the intake velocity
     * 
     */
    void updateVelocity();

public:
    /**
     * @brief Initializes the intake
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the intake
     * 
     */
    void run() override;

    /**
     * @brief Get the velocity of the intake in in/s
     * 
     * @return double The intake velocity
     */
    double getVelocity() override;

    /**
     * @brief Set the velocity of the intake
     * 
     * @param velocity The velocity of the intake in in/s
     */
    void setVelocity(double velocity) override;

    /**
     * @brief Set the voltage of the intake directly
     * 
     * @param voltage The voltage for the intake
     */
    void setVoltage(double voltage) override;

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
    void setMotors(hal::MotorGroup motors);

    /**
     * @brief Set the radius of the roller
     * 
     * @param roller_radius The radius of the roller
     */
    void setRollerRadius(double roller_radius);
};
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif