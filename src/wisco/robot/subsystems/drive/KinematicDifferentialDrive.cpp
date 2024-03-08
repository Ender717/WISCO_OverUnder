#include "wisco/robot/subsystems/drive/KinematicDifferentialDrive.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace drive
{
    void KinematicDifferentialDrive::taskLoop(void* params)
    {
        void** parameters{static_cast<void**>(params)};
        KinematicDifferentialDrive* instance{static_cast<KinematicDifferentialDrive*>(parameters[0])};

        while (true)
        {
            instance->taskUpdate();
        }
    }

    void KinematicDifferentialDrive::taskUpdate()
    {
        updateAcceleration();
        m_delayer->delay(TASK_DELAY);
    }

    void KinematicDifferentialDrive::updateAcceleration()
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

    void KinematicDifferentialDrive::initialize()
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

    void KinematicDifferentialDrive::run()
    {
        if (m_task)
        {
            void** params{static_cast<void**>(malloc(1 * sizeof(void*)))};
            params[0] = this;
            m_task->start(&KinematicDifferentialDrive::taskLoop, params);
        }
    }

    double KinematicDifferentialDrive::getLeftVelocity()
    {
        return m_left_motors.getAngularVelocity() * m_wheel_radius;
    }

    double KinematicDifferentialDrive::getRightVelocity()
    {
        return m_right_motors.getAngularVelocity() * m_wheel_radius;
    }

    void KinematicDifferentialDrive::setAcceleration(double left_acceleration, double right_acceleration)
    {
        if (m_mutex)
            m_mutex->take();
        
        m_left_acceleration = left_acceleration;
        m_right_acceleration = right_acceleration;

        if (m_mutex)
            m_mutex->give();
    } 

    void KinematicDifferentialDrive::setDelayer(std::unique_ptr<rtos::IDelayer>& delayer)
    {
        m_delayer = std::move(delayer);
    }

    void KinematicDifferentialDrive::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
    {
        m_mutex = std::move(mutex);
    }

    void KinematicDifferentialDrive::setTask(std::unique_ptr<rtos::ITask>& task)
    {
        m_task = std::move(task);
    }

    void KinematicDifferentialDrive::setLeftMotors(hal::MotorGroup left_motors)
    {
        m_left_motors = left_motors;
    }

    void KinematicDifferentialDrive::setRightMotors(hal::MotorGroup right_motors)
    {
        m_right_motors = right_motors;
    }

    void KinematicDifferentialDrive::setMass(double mass)
    {
        m_mass = mass;
    }

    void KinematicDifferentialDrive::setRadius(double radius)
    {
        m_radius = radius;
    }

    void KinematicDifferentialDrive::setMomentOfInertia(double moment_of_inertia)
    {
        m_moment_of_inertia = moment_of_inertia;
    }

    void KinematicDifferentialDrive::setGearRatio(double gear_ratio)
    {
        m_gear_ratio = gear_ratio;
    }

    void KinematicDifferentialDrive::setWheelRadius(double wheel_radius)
    {
        m_wheel_radius = wheel_radius;
    }
}
}
}
}