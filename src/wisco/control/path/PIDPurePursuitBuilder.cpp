#include "wisco/control/path/PIDPurePursuitBuilder.hpp"
#include "IPathFollower.hpp"

namespace wisco
{
namespace control
{
namespace path
{
PIDPurePursuitBuilder* PIDPurePursuitBuilder::withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
    return this;
}

PIDPurePursuitBuilder* PIDPurePursuitBuilder::withMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}

PIDPurePursuitBuilder* PIDPurePursuitBuilder::withTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

PIDPurePursuitBuilder* PIDPurePursuitBuilder::withLinearPID(PID linear_pid)
{
    m_linear_pid = linear_pid;
    return this;
}

PIDPurePursuitBuilder* PIDPurePursuitBuilder::withRotationalPID(PID rotational_pid)
{
    m_rotational_pid = rotational_pid;
    return this;
}

PIDPurePursuitBuilder* PIDPurePursuitBuilder::withFollowDistance(double follow_distance)
{
    m_follow_distance = follow_distance;
    return this;
}

PIDPurePursuitBuilder* PIDPurePursuitBuilder::withTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
    return this;
}

PIDPurePursuitBuilder* PIDPurePursuitBuilder::withTargetVelocity(double target_velocity)
{
    m_target_velocity = target_velocity;
    return this;
}

std::unique_ptr<IPathFollower> PIDPurePursuitBuilder::build()
{
    std::unique_ptr<PIDPurePursuit> pid_pure_pursuit{std::make_unique<PIDPurePursuit>()};
    pid_pure_pursuit->setDelayer(m_delayer);
    pid_pure_pursuit->setMutex(m_mutex);
    pid_pure_pursuit->setTask(m_task);
    pid_pure_pursuit->setLinearPID(m_linear_pid);
    pid_pure_pursuit->setRotationalPID(m_rotational_pid);
    pid_pure_pursuit->setFollowDistance(m_follow_distance);
    pid_pure_pursuit->setTargetTolerance(m_target_tolerance);
    pid_pure_pursuit->setTargetVelocity(m_target_velocity);
    return pid_pure_pursuit;
}
}
}
}