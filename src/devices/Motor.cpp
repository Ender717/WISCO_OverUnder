// Included headers
#include "devices/Motor.h"

Motor::Motor()
{
    port = 0;
}

Motor::Motor(uint8_t _port, pros::motor_gearset_e_t gearset, bool reversed, pros::motor_encoder_units_e_t units) : port(_port)
{
    pros::c::motor_set_gearing(port, gearset);
    pros::c::motor_set_reversed(port, reversed);
    pros::c::motor_set_encoder_units(port, units);
}

Motor::Motor(const Motor& copy) : port(copy.port)
{

}

int Motor::getAnalogVoltage(double power)
{
    return std::min(127.0, std::abs(power)) * sign<double>(power);
}

int Motor::getVelocity(double velocity)
{
    double max = 0;
    switch(pros::c::motor_get_gearing(port))
    {
    case pros::E_MOTOR_GEAR_100: { max = 100; }
    case pros::E_MOTOR_GEAR_200: { max = 200; }
    case pros::E_MOTOR_GEAR_600: { max = 600; }
    case pros::E_MOTOR_GEARSET_INVALID: { }
    }
    return std::min(max, std::abs(velocity)) * sign<double>(velocity);
}

int Motor::getVoltage(double voltage)
{
    return std::min(12000.0, std::abs(voltage)) * sign<double>(voltage);
}

void Motor::set_port(uint8_t _port)
{
    mutex.take();
    port = _port;
    mutex.give();
}

uint8_t Motor::get_port()
{
    mutex.take();
    uint8_t result = port;
    mutex.give();
    return result;
}

int Motor::move(double power)
{
    mutex.take();
    int voltage = getAnalogVoltage(power);
    int result = pros::c::motor_move(port, voltage);
    mutex.give();
    return result;
}

int Motor::move_absolute(double position, double velocity)
{
    mutex.take();
    int _velocity = getVelocity(velocity);
    int result = pros::c::motor_move_absolute(port, position, _velocity);
    mutex.give();
    return result;
}

int Motor::move_relative(double position, double velocity)
{
    mutex.take();
    int _velocity = getVelocity(velocity);
    int result = pros::c::motor_move_relative(port, position, _velocity);
    mutex.give();
    return result;
}

int Motor::move_velocity(double velocity)
{
    mutex.take();
    int _velocity = getVelocity(velocity);
    int result = pros::c::motor_move_velocity(port, _velocity);
    mutex.give();
    return result;
}

int Motor::move_voltage(double voltage)
{
    mutex.take();
    int _voltage = getVoltage(voltage);
    int result = pros::c::motor_move_voltage(port, _voltage);
    mutex.give();
    return result;
}

int Motor::brake()
{
    mutex.take();
    int result = pros::c::motor_brake(port);
    mutex.give();
    return result;
}

int Motor::modify_profiled_velocity(double velocity)
{
    mutex.take();
    int _velocity = getVelocity(velocity);
    int result = pros::c::motor_modify_profiled_velocity(port, _velocity);
    mutex.give();
    return result;
}

double Motor::get_target_position()
{
    mutex.take();
    double result = pros::c::motor_get_target_position(port);
    mutex.give();
    return result;
}

int Motor::get_target_velocity()
{
    mutex.take();
    int result = pros::c::motor_get_target_velocity(port);
    mutex.give();
    return result;
}

double Motor::get_actual_velocity()
{
    mutex.take();
    double result = pros::c::motor_get_actual_velocity(port);
    mutex.give();
    return result;
}

int Motor::get_current_draw()
{
    mutex.take();
    int result = pros::c::motor_get_current_draw(port);
    mutex.give();
    return result;
}

int Motor::get_direction()
{
    mutex.take();
    int result = pros::c::motor_get_direction(port);
    mutex.give();
    return result;
}

int Motor::get_efficiency()
{
    mutex.take();
    int result = pros::c::motor_get_efficiency(port);
    mutex.give();
    return result;
}

unsigned int Motor::get_faults()
{
    mutex.take();
    unsigned int result = pros::c::motor_get_faults(port);
    mutex.give();
    return result;
}

unsigned int Motor::get_flags()
{
    mutex.take();
    unsigned int result = pros::c::motor_get_flags(port);
    mutex.give();
    return result;
}

double Motor::get_position()
{
    mutex.take();
    double result = pros::c::motor_get_position(port);
    mutex.give();
    return result;
}

double Motor::get_power()
{
    mutex.take();
    double result = pros::c::motor_get_power(port);
    mutex.give();
    return result;
}

int Motor::get_raw_position(uint32_t* timestamp)
{
    mutex.take();
    int result = pros::c::motor_get_raw_position(port, timestamp);
    mutex.give();
    return result;
}

double Motor::get_temperature()
{
    mutex.take();
    double result = pros::c::motor_get_temperature(port);
    mutex.give();
    return result;
}

double Motor::get_torque()
{
    mutex.take();
    double result = pros::c::motor_get_torque(port);
    mutex.give();
    return result;
}

int Motor::get_voltage()
{
    mutex.take();
    int result = pros::c::motor_get_voltage(port);
    mutex.give();
    return result;
}

int Motor::get_zero_position_flag()
{
    mutex.take();
    int result = pros::c::motor_get_zero_position_flag(port);
    mutex.give();
    return result;
}

int Motor::is_stopped()
{
    mutex.take();
    int result = pros::c::motor_is_stopped(port);
    mutex.give();
    return result;
}

int Motor::is_over_current()
{
    mutex.take();
    int result = pros::c::motor_is_over_current(port);
    mutex.give();
    return result;
}

int Motor::is_over_temp()
{
    mutex.take();
    int result = pros::c::motor_is_over_temp(port);
    mutex.give();
    return result;
}

pros::motor_brake_mode_e_t Motor::get_brake_mode()
{
    mutex.take();
    pros::motor_brake_mode_e_t result = pros::c::motor_get_brake_mode(port);
    mutex.give();
    return result;
}

int Motor::get_current_limit()
{
    mutex.take();
    int result = pros::c::motor_get_current_limit(port);
    mutex.give();
    return result;
}

pros::motor_encoder_units_e_t Motor::get_encoder_units()
{
    mutex.take();
    pros::motor_encoder_units_e_t result = pros::c::motor_get_encoder_units(port);
    mutex.give();
    return result;
}

pros::motor_gearset_e_t Motor::get_gearing()
{
    mutex.take();
    pros::motor_gearset_e_t result = pros::c::motor_get_gearing(port);
    mutex.give();
    return result;
}

int Motor::get_voltage_limit()
{
    mutex.take();
    int result = pros::c::motor_get_voltage_limit(port);
    mutex.give();
    return result;
}

int Motor::is_reversed()
{
    mutex.take();
    int result = pros::c::motor_is_reversed(port);
    mutex.give();
    return result;
}

int Motor::set_brake_mode(pros::motor_brake_mode_e_t mode)
{
    mutex.take();
    int result = pros::c::motor_set_brake_mode(port, mode);
    mutex.give();
    return result;
}

int Motor::set_current_limit(int limit)
{
    mutex.take();
    int result = pros::c::motor_set_current_limit(port, limit);
    mutex.give();
    return result;
}

int Motor::set_encoder_units(pros::motor_encoder_units_e_t units)
{
    mutex.take();
    int result = pros::c::motor_set_encoder_units(port, units);
    mutex.give();
    return result;
}

int Motor::set_gearing(pros::motor_gearset_e_t gearset)
{
    mutex.take();
    int result = pros::c::motor_set_gearing(port, gearset);
    mutex.give();
    return result;
}

int Motor::set_reversed(bool reversed)
{
    mutex.take();
    int result = pros::c::motor_set_reversed(port, reversed);
    mutex.give();
    return result;
}

int Motor::set_voltage_limit(int limit)
{
    mutex.take();
    int result = pros::c::motor_set_voltage_limit(port, limit);
    mutex.give();
    return result;
}

int Motor::set_zero_position(double position)
{
    mutex.take();
    int result = pros::c::motor_set_zero_position(port, position);
    mutex.give();
    return result;
}

int Motor::tare_position()
{
    mutex.take();
    int result = pros::c::motor_tare_position(port);
    mutex.give();
    return result;
}

Motor& Motor::operator=(const Motor& rhs)
{
    mutex.take();
    port = rhs.port;
    mutex.give();
    return *this;
}