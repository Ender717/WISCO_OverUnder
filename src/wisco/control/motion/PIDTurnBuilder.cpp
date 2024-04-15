#include "wisco/control/motion/PIDTurnBuilder.hpp"

namespace wisco
{
namespace control
{
namespace motion
{
PIDTurnBuilder* PIDTurnBuilder::withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
    return this;
}

PIDTurnBuilder* PIDTurnBuilder::withMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}

PIDTurnBuilder* PIDTurnBuilder::withTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

PIDTurnBuilder* PIDTurnBuilder::withPID(PID pid)
{
    m_pid = pid;
    return this;
}

PIDTurnBuilder* PIDTurnBuilder::withTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
    return this;
}

PIDTurnBuilder* PIDTurnBuilder::withTargetVelocity(double target_velocity)
{
    m_target_velocity = target_velocity;
    return this;
}

std::unique_ptr<ITurn> PIDTurnBuilder::build()
{
    std::unique_ptr<PIDTurn> pid_turn{std::make_unique<PIDTurn>()};
    pid_turn->setDelayer(m_delayer);
    pid_turn->setMutex(m_mutex);
    pid_turn->setTask(m_task);
    pid_turn->setPID(m_pid);
    pid_turn->setTargetTolerance(m_target_tolerance);
    pid_turn->setTargetVelocity(m_target_velocity);
    return pid_turn;
}
} // namespace motion
} // namespace control
} // namespace wisco