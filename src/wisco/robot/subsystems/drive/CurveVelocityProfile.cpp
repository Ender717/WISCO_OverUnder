#include "wisco/robot/subsystems/drive/CurveVelocityProfile.hpp"

#include "pros/screen.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace drive
{
CurveVelocityProfile::CurveVelocityProfile(std::unique_ptr<rtos::IClock>& clock, double jerk_rate, double max_acceleration)
    : m_clock{std::move(clock)}, m_jerk_rate{jerk_rate}, m_max_acceleration{max_acceleration}
{

}

double CurveVelocityProfile::getAcceleration(double current_velocity, double target_velocity)
{
    double time_change{};
    if (m_clock)
    {
        double current_time = m_clock->getTime();
        time_change = current_time - last_time;
        last_time = current_time;
    }

    // TODO calculate acceleration in a better manner
    double target_acceleration = (target_velocity - current_velocity) / time_change;

    if (target_acceleration > m_max_acceleration)
        target_acceleration = m_max_acceleration;
    else if (target_acceleration < -m_max_acceleration)
        target_acceleration = -m_max_acceleration;

    if (target_acceleration > (m_current_acceleration + (m_jerk_rate * time_change)))
        target_acceleration = (m_current_acceleration + (m_jerk_rate * time_change));
    else if (target_acceleration < (m_current_acceleration - (m_jerk_rate * time_change)))
        target_acceleration = (m_current_acceleration - (m_jerk_rate * time_change));

    m_current_acceleration = target_acceleration;

    return target_acceleration;
}

void CurveVelocityProfile::setAcceleration(double acceleration)
{
    m_current_acceleration = acceleration;
    last_time = m_clock->getTime();
}
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco