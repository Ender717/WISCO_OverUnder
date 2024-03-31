#include "wisco/robot/subsystems/intake/PIDIntakeBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace intake
{
PIDIntakeBuilder* PIDIntakeBuilder::withClock(const std::unique_ptr<rtos::IClock>& clock)
{
    m_clock = clock->clone();
    return this;
}

PIDIntakeBuilder* PIDIntakeBuilder::withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
    return this;
}

PIDIntakeBuilder* PIDIntakeBuilder::withMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}

PIDIntakeBuilder* PIDIntakeBuilder::withTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

PIDIntakeBuilder* PIDIntakeBuilder::withPID(control::PID pid)
{
    m_pid = pid;
    return this;
}

PIDIntakeBuilder* PIDIntakeBuilder::withMotor(std::unique_ptr<io::IMotor>& motor)
{
    m_motors.addMotor(motor);
    return this;
}

PIDIntakeBuilder* PIDIntakeBuilder::withRollerRadius(double roller_radius)
{
    m_roller_radius = roller_radius;
    return this;
}

std::unique_ptr<IIntake> PIDIntakeBuilder::build()
{
    std::unique_ptr<PIDIntake> pid_intake{std::make_unique<PIDIntake>()};
    pid_intake->setClock(m_clock);
    pid_intake->setDelayer(m_delayer);
    pid_intake->setMutex(m_mutex);
    pid_intake->setTask(m_task);
    pid_intake->setPID(m_pid);
    pid_intake->setMotors(m_motors);
    pid_intake->setRollerRadius(m_roller_radius);
    return pid_intake;
}
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco