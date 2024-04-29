#include "wisco/robot/subsystems/elevator/PIDElevatorBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace elevator
{
PIDElevatorBuilder* PIDElevatorBuilder::withClock(const std::unique_ptr<rtos::IClock>& clock)
{
    m_clock = clock->clone();
    return this;
}

PIDElevatorBuilder* PIDElevatorBuilder::withDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
    return this;
}

PIDElevatorBuilder* PIDElevatorBuilder::withMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}

PIDElevatorBuilder* PIDElevatorBuilder::withTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

PIDElevatorBuilder* PIDElevatorBuilder::withPID(control::PID pid)
{
    m_pid = pid;
    return this;
}

PIDElevatorBuilder* PIDElevatorBuilder::withMotor(std::unique_ptr<io::IMotor>& motor)
{
    m_motors.addMotor(motor);
    return this;
}

PIDElevatorBuilder* PIDElevatorBuilder::withRotationSensor(std::unique_ptr<io::IRotationSensor>& rotation_sensor)
{
    m_rotation_sensor = std::move(rotation_sensor);
    return this;
}

PIDElevatorBuilder* PIDElevatorBuilder::withInchesPerRadian(double inches_per_radian)
{
    m_inches_per_radian = inches_per_radian;
    return this;
}

PIDElevatorBuilder* PIDElevatorBuilder::withMinimumPosition(double minimum_position)
{
    m_minimum_position = minimum_position;
    return this;
}

PIDElevatorBuilder* PIDElevatorBuilder::withMaximumPosition(double maximum_position)
{
    m_maximum_position = maximum_position;
    return this;
}

std::unique_ptr<IElevator> PIDElevatorBuilder::build()
{
    std::unique_ptr<PIDElevator> pid_elevator{std::make_unique<PIDElevator>()};
    pid_elevator->setClock(m_clock);
    pid_elevator->setDelayer(m_delayer);
    pid_elevator->setMutex(m_mutex);
    pid_elevator->setTask(m_task);
    pid_elevator->setPID(m_pid);
    pid_elevator->setMotors(m_motors);
    if (m_rotation_sensor)
        pid_elevator->setRotationSensor(m_rotation_sensor);
    pid_elevator->setInchesPerRadian(m_inches_per_radian);
    pid_elevator->setMinimumPosition(m_minimum_position);
    pid_elevator->setMaximumPosition(m_maximum_position);
    return pid_elevator;
}
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco