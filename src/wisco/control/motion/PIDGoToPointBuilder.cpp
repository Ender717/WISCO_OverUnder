#include "wisco/control/motion/PIDGoToPointBuilder.hpp"

namespace wisco
{
namespace control
{
namespace motion
{
PIDGoToPointBuilder* PIDGoToPointBuilder::withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
    return this;
}

PIDGoToPointBuilder* PIDGoToPointBuilder::withMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}   

PIDGoToPointBuilder* PIDGoToPointBuilder::withTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

PIDGoToPointBuilder* PIDGoToPointBuilder::withLinearPID(PID linear_pid)
{
    m_linear_pid = linear_pid;
    return this;
}

PIDGoToPointBuilder* PIDGoToPointBuilder::withRotationalPID(PID rotational_pid)
{
    m_rotational_pid = rotational_pid;
    return this;
}

PIDGoToPointBuilder* PIDGoToPointBuilder::withTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
    return this;
}

PIDGoToPointBuilder* PIDGoToPointBuilder::withTargetVelocity(double target_velocity)
{
    m_target_velocity = target_velocity;
    return this;
}

std::unique_ptr<IGoToPoint> PIDGoToPointBuilder::build()
{
    std::unique_ptr<PIDGoToPoint> pid_go_to_point{std::make_unique<PIDGoToPoint>()};
    pid_go_to_point->setDelayer(m_delayer);
    pid_go_to_point->setMutex(m_mutex);
    pid_go_to_point->setTask(m_task);
    pid_go_to_point->setLinearPID(m_linear_pid);
    pid_go_to_point->setRotationalPID(m_rotational_pid);
    pid_go_to_point->setTargetTolerance(m_target_tolerance);
    pid_go_to_point->setTargetVelocity(m_target_velocity);
    return pid_go_to_point;
}
} // namespace motion
} // namespace control
} // namespace wisco