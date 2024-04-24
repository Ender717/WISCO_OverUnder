#ifndef WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_PID_ELEVATOR_HPP
#define WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_PID_ELEVATOR_HPP

#include <cfloat>
#include <memory>

#include "wisco/control/PID.hpp"
#include "wisco/hal/MotorGroup.hpp"
#include "wisco/io/IRotationSensor.hpp"
#include "wisco/rtos/IClock.hpp"
#include "wisco/rtos/IDelayer.hpp"
#include "wisco/rtos/IMutex.hpp"
#include "wisco/rtos/ITask.hpp"

#include "IElevator.hpp"

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
 * @brief Namespace for elevator classes
 * @author Nathan Sandvig
 * 
 */
namespace elevator
{

/**
 * @brief An elevator controller with PID position control
 * @author Nathan Sandvig
 * 
 */
class PIDElevator : public IElevator
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
     * @brief The motors on the elevator
     * 
     */
    hal::MotorGroup m_motors{};

    /**
     * @brief The rotation sensor on the elevator
     * 
     */
    std::unique_ptr<io::IRotationSensor> m_rotation_sensor{};

    /**
     * @brief The number of movement inches per radian
     * 
     */
    double m_inches_per_radian{};

    /**
     * @brief The position setting of the elevator
     * 
     */
    double m_position{};

    /**
     * @brief Whether or not the elevator is calibrating
     * 
     */
    bool calibrating{};

    /**
     * @brief The time the elevator started calibrating
     * 
     */
    uint32_t calibrate_time{};

    /**
     * @brief Whether or not it's in manual control mode
     * 
     */
    bool manual{};

    /**
     * @brief Runs all the object-specific updates in the task loop
     * 
     */
    void taskUpdate();

    /**
     * @brief Updates the elevator position
     * 
     */
    void updatePosition();

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
     * @brief Get the position of the elevator in inches
     * 
     * @return double The elevator position
     */
    double getPosition() override;

    /**
     * @brief Set the position of the elevator in inches
     * 
     * @param position The position of the elevator
     */
    void setPosition(double position) override;

    /**
     * @brief Set the voltage of the elevator
     * 
     * @param voltage The voltage of the elevator
     */
    void setVoltage(double voltage) override;

    /**
     * @brief Calibrates the elevator position
     * 
     */
    void calibrate() override;

    /**
     * @brief Checks if the elevator is calibrating
     * 
     * @return true The elevator is calibrating
     * @return false The elevator is not calibrating
     */
    bool isCalibrating() override;

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
     * @brief Set the rotation sensor
     * 
     * @param rotation_sensor The rotation sensor
     */
    void setRotationSensor(std::unique_ptr<io::IRotationSensor>& rotation_sensor);

    /**
     * @brief Set the inches per radian of the elevator
     * 
     * @param inches_per_radian The inches per radian of the elevator
     */
    void setInchesPerRadian(double inches_per_radian);
};
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif