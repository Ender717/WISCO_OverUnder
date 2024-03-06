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
        
        // TODO kinematic calculation for voltage

        if (m_mutex)
            m_mutex->give();
    }

    void DifferentialDrive::initialize()
    {
        m_left_motors.initialize();
        m_right_motors.initialize();
        m_left_acceleration = 0;
        m_right_acceleration = 0;
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

    void DifferentialDrive::setClock(std::unique_ptr<rtos::IClock>& clock)
    {
        m_clock = std::move(clock);
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