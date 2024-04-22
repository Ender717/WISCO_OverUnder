#include "wisco/control/motion/PIDDriveStraightBuilder.hpp"

namespace wisco
{
namespace control
{
namespace motion
{
PIDDriveStraightBuilder* PIDDriveStraightBuilder::withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
    return this;
}

PIDDriveStraightBuilder* PIDDriveStraightBuilder::withMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}   

PIDDriveStraightBuilder* PIDDriveStraightBuilder::withTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

PIDDriveStraightBuilder* PIDDriveStraightBuilder::withLinearPID(PID linear_pid)
{
    m_linear_pid = linear_pid;
    return this;
}

PIDDriveStraightBuilder* PIDDriveStraightBuilder::withRotationalPID(PID rotational_pid)
{
    m_rotational_pid = rotational_pid;
    return this;
}

PIDDriveStraightBuilder* PIDDriveStraightBuilder::withTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
    return this;
}

PIDDriveStraightBuilder* PIDDriveStraightBuilder::withTargetVelocity(double target_velocity)
{
    m_target_velocity = target_velocity;
    return this;
}

std::unique_ptr<IDriveStraight> PIDDriveStraightBuilder::build()
{
    std::unique_ptr<PIDDriveStraight> pid_drive_straight{std::make_unique<PIDDriveStraight>()};
    pid_drive_straight->setDelayer(m_delayer);
    pid_drive_straight->setMutex(m_mutex);
    pid_drive_straight->setTask(m_task);
    pid_drive_straight->setLinearPID(m_linear_pid);
    pid_drive_straight->setRotationalPID(m_rotational_pid);
    pid_drive_straight->setTargetTolerance(m_target_tolerance);
    pid_drive_straight->setTargetVelocity(m_target_velocity);
    return pid_drive_straight;
}
} // namespace motion
} // namespace control
} // namespace wisco