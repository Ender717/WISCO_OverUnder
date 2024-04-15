#include "wisco/robot/subsystems/intake/PIDIntake.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace intake
{
void PIDIntake::taskLoop(void* params)
{
    PIDIntake* instance{static_cast<PIDIntake*>(params)};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDIntake::taskUpdate()
{
    if (velocity_control)
        updateVelocity();
    m_delayer->delay(TASK_DELAY);
}

void PIDIntake::updateVelocity()
{
    if (m_mutex)
        m_mutex->take();

    double velocity{getVelocity()};
    double voltage{m_pid.getControlValue(velocity, m_velocity)};
    m_motors.setVoltage(voltage);

    if (m_mutex)
        m_mutex->give();
}

void PIDIntake::initialize()
{
    m_pid.reset();
    m_motors.initialize();
}

void PIDIntake::run()
{
    if (m_task)
        m_task->start(&PIDIntake::taskLoop, this);
}

double PIDIntake::getVelocity()
{
    return m_motors.getAngularVelocity() * m_roller_radius;
}

void PIDIntake::setVelocity(double velocity)
{
    if (m_mutex)
        m_mutex->take();
    
    m_velocity = velocity;
    velocity_control = true;

    if (m_mutex)
        m_mutex->give();
}

void PIDIntake::setVoltage(double voltage)
{
    if (m_mutex)
        m_mutex->take();
    
    m_pid.reset();
    m_motors.setVoltage(voltage);
    velocity_control = false;

    if (m_mutex)
        m_mutex->give();
}

void PIDIntake::setClock(const std::unique_ptr<rtos::IClock>& clock)
{
    m_clock = clock->clone();
}

void PIDIntake::setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
}

void PIDIntake::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
}

void PIDIntake::setTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
}

void PIDIntake::setPID(control::PID pid)
{
    m_pid = pid;
}

void PIDIntake::setMotors(hal::MotorGroup& motors)
{
    m_motors = motors;
}

void PIDIntake::setRollerRadius(double roller_radius)
{
    m_roller_radius = roller_radius;
}
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco