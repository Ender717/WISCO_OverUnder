#include "wisco/robot/subsystems/drive/DifferentialDriveBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace drive
{
DifferentialDriveBuilder* DifferentialDriveBuilder::withDelayer(std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = std::move(delayer);
    return this;
}

DifferentialDriveBuilder* DifferentialDriveBuilder::withMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
    return this;
}

DifferentialDriveBuilder* DifferentialDriveBuilder::withTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
    return this;
}

DifferentialDriveBuilder* DifferentialDriveBuilder::withLeftMotors(hal::MotorGroup left_motors)
{
    m_left_motors = left_motors;
    return this;
}

DifferentialDriveBuilder* DifferentialDriveBuilder::withRightMotors(hal::MotorGroup right_motors)
{
    m_right_motors = right_motors;
    return this;
}

DifferentialDriveBuilder* DifferentialDriveBuilder::withMass(double mass)
{
    m_mass = mass;
    return this;
}

DifferentialDriveBuilder* DifferentialDriveBuilder::withRadius(double radius)
{
    m_radius = radius;
    return this;
}

DifferentialDriveBuilder* DifferentialDriveBuilder::withMomentOfInertia(double moment_of_inertia)
{
    m_moment_of_inertia = moment_of_inertia;
    return this;
}

DifferentialDriveBuilder* DifferentialDriveBuilder::withGearRatio(double gear_ratio)
{
    m_gear_ratio = gear_ratio;
    return this;
}

DifferentialDriveBuilder* DifferentialDriveBuilder::withWheelRadius(double wheel_radius)
{
    m_wheel_radius = wheel_radius;
    return this;
}

std::unique_ptr<IDifferentialDrive> DifferentialDriveBuilder::build()
{
    std::unique_ptr<DifferentialDrive> differential_drive{std::make_unique<DifferentialDrive>()};
    differential_drive->setDelayer(m_delayer);
    differential_drive->setMutex(m_mutex);
    differential_drive->setTask(m_task);
    differential_drive->setLeftMotors(m_left_motors);
    differential_drive->setRightMotors(m_right_motors);
    differential_drive->setMass(m_mass);
    differential_drive->setRadius(m_radius);
    differential_drive->setMomentOfInertia(m_moment_of_inertia);
    differential_drive->setGearRatio(m_gear_ratio);
    differential_drive->setWheelRadius(m_wheel_radius);
    return differential_drive;
}
}
}
}
}