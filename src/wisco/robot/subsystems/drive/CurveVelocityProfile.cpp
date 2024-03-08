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
    // TODO calculate acceleration using profile
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