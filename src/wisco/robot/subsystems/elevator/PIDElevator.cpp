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
    PIDElevator* instance{static_cast<PIDElevator*>(params)};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDElevator::taskUpdate()
{
    if (m_mutex)
        m_mutex->take();
    uint32_t calibration_time{UINT32_MAX};
    if (m_clock)
        calibration_time = m_clock->getTime() - calibrate_time;
    if (calibrating && m_motors.getAngularVelocity() >= 0.0 && calibration_time >= 500)
    {
        m_motors.setPosition(0);
        calibrating = false;
    }
    if (!calibrating && !manual)
        updatePosition();
    if (m_mutex)
        m_mutex->give();
    m_delayer->delay(TASK_DELAY);
}

void PIDElevator::updatePosition()
{
    double current_position{getPosition()};
    double voltage{m_pid.getControlValue(current_position, m_position)};
    m_motors.setVoltage(voltage);
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
        m_task->start(&PIDElevator::taskLoop, this);
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
    
    position = std::min(m_maximum_position, position);
    position = std::max(m_minimum_position, position);
    m_position = position;
    manual = false;

    if (m_mutex)
        m_mutex->give();
}

void PIDElevator::setVoltage(double voltage)
{
    if (m_mutex)
        m_mutex->take();

    manual = true;
    m_motors.setVoltage(voltage);

    if (m_mutex)
        m_mutex->give();
}

void PIDElevator::calibrate()
{
    if (m_mutex)
        m_mutex->take();
    
    calibrating = true;
    m_motors.setVoltage(-12.0);
    if (m_clock)
        calibrate_time = m_clock->getTime();

    if (m_mutex)
        m_mutex->give();
}

bool PIDElevator::isCalibrating()
{
    return calibrating;
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

void PIDElevator::setMinimumPosition(double minimum_position)
{
    m_minimum_position = minimum_position;
}

void PIDElevator::setMaximumPosition(double maximum_position)
{
    m_maximum_position = maximum_position;
}
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace wisco