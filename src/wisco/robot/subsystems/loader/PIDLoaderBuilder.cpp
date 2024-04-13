#include "wisco/robot/subsystems/loader/PIDLoaderBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace loader
{
PIDLoaderBuilder* PIDLoaderBuilder::withClock(const std::unique_ptr<rtos::IClock>& clock)
{
    m_clock = clock->clone();
    return this;
}

PIDLoaderBuilder* PIDLoaderBuilder::withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
    return this;
}

PIDLoaderBuilder* PIDLoaderBuilder::withMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}

PIDLoaderBuilder* PIDLoaderBuilder::withTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

PIDLoaderBuilder* PIDLoaderBuilder::withPID(control::PID pid)
{
    m_pid = pid;
    return this;
}

PIDLoaderBuilder* PIDLoaderBuilder::withMotor(std::unique_ptr<io::IMotor>& motor)
{
    m_motors.addMotor(motor);
    return this;
}

PIDLoaderBuilder* PIDLoaderBuilder::withMatchLoadPosition(double match_load_position)
{
    m_match_load_position = match_load_position;
    return this;
}

PIDLoaderBuilder* PIDLoaderBuilder::withReadyPosition(double ready_position)
{
    m_ready_position = ready_position;
    return this;
}

PIDLoaderBuilder* PIDLoaderBuilder::withPositionTolerance(double position_tolerance)
{
    m_position_tolerance = position_tolerance;
    return this;
}

std::unique_ptr<ILoader> PIDLoaderBuilder::build()
{
    std::unique_ptr<PIDLoader> pid_loader{std::make_unique<PIDLoader>()};
    pid_loader->setClock(m_clock);
    pid_loader->setDelayer(m_delayer);
    pid_loader->setMutex(m_mutex);
    pid_loader->setTask(m_task);
    pid_loader->setMotors(m_motors);
    pid_loader->setPID(m_pid);
    pid_loader->setMatchLoadPosition(m_match_load_position);
    pid_loader->setReadyPosition(m_ready_position);
    pid_loader->setPositionTolerance(m_position_tolerance);
    return pid_loader;
}
} // namespace loader
} // namespace subsystems
} // namespace robot
} // namespace wisco