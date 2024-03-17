#include "wisco/control/PID.hpp"

namespace wisco
{
namespace control
{
PID::PID(std::unique_ptr<rtos::IClock>& clock, double kp, double ki, double kd)
    : m_clock{std::move(clock)}, m_kp{kp}, m_ki{ki}, m_kd{kd}
{

}

double PID::getControlValue(double current, double target)
{
    double time_change{};
    if (m_clock)
    {
        double current_time = m_clock->getTime();
        time_change = current_time - last_time;
        last_time = current_time;
    }

    double error{target - current};
    accumulated_error += (error * time_change);
    double error_change{(error - last_error) / time_change};
    last_error = error;

    return (m_kp * error) + (m_ki * accumulated_error) + (m_kd * error_change);
}
} // namespace control
} // namespace wisco