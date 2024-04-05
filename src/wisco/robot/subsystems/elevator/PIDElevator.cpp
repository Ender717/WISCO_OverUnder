#include "wisco/robot/subsystems/elevator/PIDElevator.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace elevator
{
void PIDElevator::taskLoop(void* params)
{
    void** parameters{static_cast<void**>(params)};
    PIDElevator* instance{static_cast<PIDElevator*>(parameters[0])};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDElevator::taskUpdate()
{
    updatePosition();
    m_delayer->delay(TASK_DELAY);
}

void PIDElevator::updatePosition()
{
    if (m_mutex)
        m_mutex->take();

    double voltage{m_pid.getControlValue(getPosition(), m_position)};
    m_motors.setVoltage(voltage);

    if (m_mutex)
        m_mutex->give();
}

void PIDElevator::initialize()
{
    m_pid.reset();
    m_motors.initialize();
    if (m_rotation_sensor)
        m_rotation_sensor->initialize();
}

void PIDElevator::run()
{
    if (m_task)
    {
        void** params{static_cast<void**>(malloc(1 * sizeof(void*)))};
        params[0] = this;
        m_task->start(&PIDElevator::taskLoop, params);
    }
}

double PIDElevator::getPosition()
{
    double position{};
    if (m_rotation_sensor)
    {
        position = m_rotation_sensor->getRotation() * m_inches_per_radian;
    }
    else
    {
        position = m_motors.getPosition() * m_inches_per_radian;
    }
    return position;
}

void PIDElevator::setPosition(double position)
{
    if (m_mutex)
        m_mutex->take();
    
    m_position = position;

    if (m_mutex)
        m_mutex->give();
}

void PIDElevator::setClock(const std::unique_ptr<rtos::IClock>& clock)
{
    m_clock = clock->clone();
}

void PIDElevator::setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
}

void PIDElevator::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
}

void PIDElevator::setTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
}

void PIDElevator::setPID(control::PID pid)
{
    m_pid = pid;
}

void PIDElevator::setMotors(hal::MotorGroup& motors)
{
    m_motors = motors;
}

void PIDElevator::setRotationSensor(std::unique_ptr<io::IRotationSensor>& rotation_sensor)
{
    m_rotation_sensor = std::move(rotation_sensor);
}

void PIDElevator::setInchesPerRadian(double inches_per_radian)
{
    m_inches_per_radian = inches_per_radian;
}
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace wisco