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
    std::unique_ptr<rtos::IClock> m_clock{};
    std::unique_ptr<rtos::IDelayer> m_delayer{};
    std::unique_ptr<rtos::IMutex> m_mutex{};
    std::unique_ptr<rtos::ITask> m_task{};
    control::PID m_pid{};
public:

};
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif