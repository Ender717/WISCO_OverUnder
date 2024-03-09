#include "wisco/robot/subsystems/drive/CurveVelocityProfile.hpp"

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

double CurveVelocityProfile::getAcceleration(double target_velocity)
{
    double time_change{};
    if (m_clock)
    {
        double current_time = m_clock->getTime();
        time_change = current_time - last_time;
        last_time = current_time;
    }

    double acceleration{};

    double next_acceleration{m_current_acceleration + m_jerk_rate};
    next_acceleration = std::min(next_acceleration, m_max_acceleration);
    next_acceleration = std::max(next_acceleration, -m_max_acceleration);

    double next_step{(m_current_acceleration + next_acceleration) / 2 * time_change};
    double trapezoid{std::pow(next_acceleration, 2) / (2 * m_jerk_rate)};
    if (next_step + trapezoid  >= target_velocity)
    {
        double timestep{m_jerk_rate * time_change};
        acceleration = static_cast<int>(next_acceleration / timestep) * timestep;
    }
    else
    {
        acceleration = next_acceleration;
    }

    m_current_acceleration = acceleration;

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