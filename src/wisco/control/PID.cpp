#include "wisco/control/PID.hpp"

namespace wisco
{
namespace control
{
PID::PID(std::unique_ptr<rtos::IClock>& clock, double kp, double ki, double kd)
    : m_clock{std::move(clock)}, m_kp{kp}, m_ki{ki}, m_kd{kd}
{

}

PID::PID(const PID& copy) 
    : m_clock{copy.m_clock->clone()}, 
      m_kp{copy.m_kp}, 
      m_ki{copy.m_ki}, 
      m_kd{copy.m_kd},
      accumulated_error{copy.accumulated_error},
      last_error{copy.last_error},
      last_time{copy.last_time}
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

PID& PID::operator=(const PID& rhs)
{
    m_clock = rhs.m_clock->clone();
    m_kp = rhs.m_kp;
    m_ki = rhs.m_ki;
    m_kd = rhs.m_kd;
    accumulated_error = rhs.accumulated_error;
    last_error = rhs.last_error;
    last_time = rhs.last_time;
    return *this;
}
} // namespace control
} // namespace wisco