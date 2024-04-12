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
    void** parameters{static_cast<void**>(params)};
    PIDLoader* instance{static_cast<PIDLoader*>(parameters[0])};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDLoader::taskUpdate()
{
    updatePosition();
    m_delayer->delay(TASK_DELAY);
}

void PIDLoader::updatePosition()
{
    if (m_mutex)
        m_mutex->take();
    
    double voltage{m_pid.getControlValue(m_motors.getPosition(), target_position)};
    m_motors.setVoltage(voltage);

    if (m_mutex)
        m_mutex->give();
}

void PIDLoader::initialize()
{
    m_pid.reset();
    m_motors.initialize();
}

void PIDLoader::run()
{
    if (m_task)
    {
        void** params{static_cast<void**>(malloc(1 * sizeof(void*)))};
        params[0] = this;
        m_task->start(&PIDLoader::taskLoop, params);
    }
}

void PIDLoader::doMatchLoad()
{

}

bool PIDLoader::isLoaded()
{

}

bool PIDLoader::isReady()
{

}

void PIDLoader::setClock(const std::unique_ptr<rtos::IClock>& clock)
{

}

void PIDLoader::setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{

}

void PIDLoader::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{

}

void PIDLoader::setTask(std::unique_ptr<rtos::ITask>& task)
{

}

void PIDLoader::setPID(control::PID pid)
{

}

void PIDLoader::setMotors(hal::MotorGroup& motors)
{

}

void PIDLoader::setMatchLoadPosition(double match_load_position)
{

}

void PIDLoader::setReadyPosition(double ready_position)
{

}

void PIDLoader::setPositionTolerance(double position_tolerance)
{

}
} // namespace loader
} // namespace subsystems
} // namespace robot
} // namespace wisco