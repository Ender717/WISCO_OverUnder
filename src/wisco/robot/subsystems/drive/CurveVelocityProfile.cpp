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

    double acceleration{};

    // TODO calculate acceleration

    return acceleration;
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