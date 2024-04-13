#include "wisco/control/boomerang/PIDBoomerangBuilder.hpp"

namespace wisco
{
namespace control
{
namespace boomerang
{
PIDBoomerangBuilder* PIDBoomerangBuilder::withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
    return this;
}

PIDBoomerangBuilder* PIDBoomerangBuilder::withMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}

PIDBoomerangBuilder* PIDBoomerangBuilder::withTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

PIDBoomerangBuilder* PIDBoomerangBuilder::withLinearPID(PID linear_pid)
{
    m_linear_pid = linear_pid;
    return this;
}

PIDBoomerangBuilder* PIDBoomerangBuilder::withRotationalPID(PID rotational_pid)
{
    m_rotational_pid = rotational_pid;
    return this;
}

PIDBoomerangBuilder* PIDBoomerangBuilder::withLead(double lead)
{
    m_lead = lead;
    return this;
}

PIDBoomerangBuilder* PIDBoomerangBuilder::withTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
    return this;
}

std::unique_ptr<IBoomerang> PIDBoomerangBuilder::build()
{
    std::unique_ptr<PIDBoomerang> pid_boomerang{std::make_unique<PIDBoomerang>()};
    pid_boomerang->setDelayer(m_delayer);
    pid_boomerang->setMutex(m_mutex);
    pid_boomerang->setTask(m_task);
    pid_boomerang->setLinearPID(m_linear_pid);
    pid_boomerang->setRotationalPID(m_rotational_pid);
    pid_boomerang->setLead(m_lead);
    pid_boomerang->setTargetTolerance(m_target_tolerance);
    return pid_boomerang;
}
}
}
}