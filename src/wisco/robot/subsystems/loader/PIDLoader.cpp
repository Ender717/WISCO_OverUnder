#include "wisco/robot/subsystems/loader/PIDLoader.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace loader
{
void PIDLoader::taskLoop(void* params)
{
    PIDLoader* instance{static_cast<PIDLoader*>(params)};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDLoader::taskUpdate()
{
    if (m_mutex)
        m_mutex->take();
    updateState();
    updatePosition();
    if (m_mutex)
        m_mutex->give();
    
    m_delayer->delay(TASK_DELAY);
}

void PIDLoader::updateState()
{
    double position{getPosition()};
    switch (state)
    {
    case EState::READY:
        break;
    case EState::READYING:
        if (std::abs(position - m_ready_position) < m_position_tolerance)
            state = EState::READY;
        break;
    case EState::LOADED:
        break;
    case EState::LOADING:
        if (std::abs(position - m_match_load_position) < m_position_tolerance)
            state = EState::LOADED;
        break;
    }
}

void PIDLoader::updatePosition()
{    
    double voltage{m_pid.getControlValue(getPosition(), target_position)};
    m_motors.setVoltage(voltage);
}

double PIDLoader::getPosition()
{
    return m_motors.getPosition();
}

void PIDLoader::initialize()
{
    m_pid.reset();
    m_motors.initialize();
}

void PIDLoader::run()
{
    if (m_task)
        m_task->start(&PIDLoader::taskLoop, this);
}

void PIDLoader::doLoad()
{
    if (m_mutex)
        m_mutex->take();

    if (state != EState::LOADED)
    {
        state = EState::LOADING;
        target_position = m_match_load_position;
    }

    if (m_mutex)
        m_mutex->give();
}

void PIDLoader::doReady()
{
    if (m_mutex)
        m_mutex->take();

    if (state != EState::READY)
    {
        state = EState::READYING;
        target_position = m_ready_position;
    }

    if (m_mutex)
        m_mutex->give();
}

bool PIDLoader::isLoaded()
{
    return state == EState::LOADED;
}

bool PIDLoader::isReady()
{
    return state == EState::READY;
}

void PIDLoader::setClock(const std::unique_ptr<rtos::IClock>& clock)
{
    m_clock = clock->clone();
}

void PIDLoader::setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
}

void PIDLoader::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
}

void PIDLoader::setTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
}

void PIDLoader::setPID(control::PID pid)
{
    m_pid = pid;
}

void PIDLoader::setMotors(hal::MotorGroup& motors)
{
    m_motors = motors;
}

void PIDLoader::setMatchLoadPosition(double match_load_position)
{
    m_match_load_position = match_load_position;
}

void PIDLoader::setReadyPosition(double ready_position)
{
    m_ready_position = ready_position;
}

void PIDLoader::setPositionTolerance(double position_tolerance)
{
    m_position_tolerance = position_tolerance;
}
} // namespace loader
} // namespace subsystems
} // namespace robot
} // namespace wisco