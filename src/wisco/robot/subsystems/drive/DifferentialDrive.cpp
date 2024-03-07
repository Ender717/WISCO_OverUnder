#include "wisco/robot/subsystems/drive/DifferentialDrive.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace drive
{
    void DifferentialDrive::taskLoop(void* params)
    {
        void** parameters{static_cast<void**>(params)};
        DifferentialDrive* instance{static_cast<DifferentialDrive*>(parameters[0])};

        while (true)
        {
            instance->taskUpdate();
        }
    }

    void DifferentialDrive::taskUpdate()
    {
        updateAcceleration();
        m_delayer->delay(TASK_DELAY);
    }

    void DifferentialDrive::updateAcceleration()
    {
        if (m_mutex)
            m_mutex->take();
        
        double right_velocity{getRightVelocity()};
        double left_velocity{getLeftVelocity()};

        double right_voltage{(c5 * m_right_acceleration - 
                              c6 * m_left_acceleration - 
                              (std::pow(c5, 2) - std::pow(c6, 2)) * c3 * right_velocity)
                             /
                             ((std::pow(c5, 2) - std::pow(c6, 2)) * c4)};
        double left_voltage{(m_right_acceleration - 
                             c1 * c6 * left_velocity -
                             c5 * (c3 * right_velocity + c4 * right_voltage))
                            /
                            (c2 * c6)};

        m_left_motors.setVoltage(left_voltage);
        m_right_motors.setVoltage(right_voltage);

        if (m_mutex)
            m_mutex->give();
    }

    void DifferentialDrive::initialize()
    {
        m_left_motors.initialize();
        m_right_motors.initialize();
        m_left_acceleration = 0;
        m_right_acceleration = 0;

        c1 = (-1 * std::pow(m_left_motors.getGearRatio() * m_gear_ratio, 2) * m_left_motors.getTorqueConstant())
            / (m_left_motors.getAngularVelocityConstant() * m_left_motors.getResistance() * std::pow(m_wheel_radius, 2));
        c2 = (m_left_motors.getGearRatio() * m_gear_ratio * m_left_motors.getTorqueConstant())
            / (m_left_motors.getResistance() * m_wheel_radius);
        c3 = (-1 * std::pow(m_right_motors.getGearRatio() * m_gear_ratio, 2) * m_right_motors.getTorqueConstant())
            / (m_right_motors.getAngularVelocityConstant() * m_right_motors.getResistance() * std::pow(m_wheel_radius, 2));        
        c4 = (m_right_motors.getGearRatio() * m_gear_ratio * m_right_motors.getTorqueConstant())
            / (m_right_motors.getResistance() * m_wheel_radius);
        c5 = (1 / m_mass) + (std::pow(m_radius, 2) / m_moment_of_inertia);
        c6 = (1 / m_mass) - (std::pow(m_radius, 2) / m_moment_of_inertia);
    }

    void DifferentialDrive::run()
    {
        if (m_task)
        {
            void** params{static_cast<void**>(malloc(1 * sizeof(void*)))};
            params[0] = this;
            m_task->start(&DifferentialDrive::taskLoop, params);
        }
    }

    double DifferentialDrive::getLeftVelocity()
    {
        return m_left_motors.getAngularVelocity() * m_wheel_radius;
    }

    double DifferentialDrive::getRightVelocity()
    {
        return m_right_motors.getAngularVelocity() * m_wheel_radius;
    }

    void DifferentialDrive::setAcceleration(double left_acceleration, double right_acceleration)
    {
        if (m_mutex)
            m_mutex->take();
        
        m_left_acceleration = left_acceleration;
        m_right_acceleration = right_acceleration;

        if (m_mutex)
            m_mutex->give();
    } 

    void DifferentialDrive::setDelayer(std::unique_ptr<rtos::IDelayer>& delayer)
    {
        m_delayer = std::move(delayer);
    }

    void DifferentialDrive::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
    {
        m_mutex = std::move(mutex);
    }

    void DifferentialDrive::setTask(std::unique_ptr<rtos::ITask>& task)
    {
        m_task = std::move(task);
    }

    void DifferentialDrive::setLeftMotors(hal::MotorGroup left_motors)
    {
        m_left_motors = left_motors;
    }

    void DifferentialDrive::setRightMotors(hal::MotorGroup right_motors)
    {
        m_right_motors = right_motors;
    }

    void DifferentialDrive::setMass(double mass)
    {
        m_mass = mass;
    }

    void DifferentialDrive::setRadius(double radius)
    {
        m_radius = radius;
    }

    void DifferentialDrive::setMomentOfInertia(double moment_of_inertia)
    {
        m_moment_of_inertia = moment_of_inertia;
    }

    void DifferentialDrive::setGearRatio(double gear_ratio)
    {
        m_gear_ratio = gear_ratio;
    }

    void DifferentialDrive::setWheelRadius(double wheel_radius)
    {
        m_wheel_radius = wheel_radius;
    }
}
}
}
}