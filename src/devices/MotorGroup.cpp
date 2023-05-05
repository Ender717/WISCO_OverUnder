// Included headers
#include "devices/MotorGroup.h"

MotorGroup::MotorGroup()
{
    size = 0;
}

MotorGroup::MotorGroup(const MotorGroup& copy)
{
    for (int i = 0; i < copy.size; i++)
        motors[i] = copy.motors[i];
    size = copy.size;
}

void MotorGroup::add_motor(Motor& motor)
{
    mutex.take();
    if (size != MAX_SIZE)
        motors[size++] = motor;
    mutex.give();
}

int MotorGroup::get_size()
{
    mutex.take();
    int result = size;
    mutex.give();
    return result;
}

uint8_t* MotorGroup::get_ports()
{
    static uint8_t ports[MAX_SIZE];
    mutex.take();
    for (int i = 0; i < MAX_SIZE; i++)
        ports[i] = motors[i].get_port();
    mutex.give();
    return ports;
}

void MotorGroup::move(double power)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].move(power);
    mutex.give();
}

void MotorGroup::move_absolute(double position, double velocity)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].move_absolute(position, velocity);
    mutex.give();
}

void MotorGroup::move_relative(double position, double velocity)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].move_relative(position, velocity);
    mutex.give();
}

void MotorGroup::move_velocity(double velocity)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].move_velocity(velocity);
    mutex.give();
}

void MotorGroup::move_voltage(double voltage)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].move_voltage(voltage);
    mutex.give();
}

void MotorGroup::brake()
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].brake();
    mutex.give();
}

void MotorGroup::modify_profiled_velocity(double velocity)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].modify_profiled_velocity(velocity);
    mutex.give();
}

double MotorGroup::get_target_position()
{
    mutex.take();
    double position = motors[0].get_target_position();
    mutex.give();
    return position;
}

int MotorGroup::get_target_velocity()
{
    mutex.take();
    int velocity = motors[0].get_target_velocity();
    mutex.give();
    return velocity;
}

double MotorGroup::get_actual_velocity()
{
    double velocity = 0.0;
    mutex.take();
    for (int i = 0; i < size; i++)
        velocity += motors[i].get_actual_velocity();
    if (size != 0)
        velocity /= size;
    mutex.give();
    return velocity;
}

int MotorGroup::get_current_draw()
{
    int current = 0;
    mutex.take();
    for (int i = 0; i < size; i++)
        current += motors[i].get_current_draw();
    if (size != 0)
        current /= size;
    mutex.give();
    return current;
}

int MotorGroup::get_direction()
{
    mutex.take();
    int direction = motors[0].get_direction();
    mutex.give();
    return direction;
}

int MotorGroup::get_efficiency()
{
    int efficiency = 0;
    mutex.take();
    for (int i = 0; i < size; i++)
        efficiency += motors[i].get_efficiency();
    if (size != 0)
        efficiency /= size;
    mutex.give();
    return efficiency;
}

int MotorGroup::get_faults()
{
    int faults = 0;
    mutex.take();
    for (int i = 0; i < size; i++)
        faults &= motors[i].get_faults();
    mutex.give();
    return faults;
}

int MotorGroup::get_flags()
{
    int flags = 0;
    mutex.take();
    for (int i = 0; i < size; i++)
        flags &= motors[i].get_flags();
    mutex.give();
    return flags;
}

double MotorGroup::get_position()
{
    double position = 0.0;
    mutex.take();
    for (int i = 0; i < size; i++)
        position += motors[i].get_position();
    if (size != 0)
        position /= size;
    mutex.give();
    return position;
}

double MotorGroup::get_power()
{
    double power = 0.0;
    mutex.take();
    for (int i = 0; i < size; i++)
        power += motors[i].get_power();
    if (size != 0)
        power /= size;
    mutex.give();
    return power;
}

int MotorGroup::get_raw_position(uint32_t* timestamp)
{
    int position = 0;
    mutex.take();
    for (int i = 0; i < size; i++)
        position += motors[i].get_raw_position(timestamp);
    if (size != 0)
        position /= size;
    mutex.give();
    return position;
}

double MotorGroup::get_temperature()
{
    double temperature = 0.0;
    mutex.take();
    for (int i = 0; i < size; i++)
        temperature += motors[i].get_temperature();
    if (size != 0)
        temperature /= size;
    mutex.give();
    return temperature;
}

double MotorGroup::get_torque()
{
    double torque = 0.0;
    mutex.take();
    for (int i = 0; i < size; i++)
        torque += motors[i].get_torque();
    if (size != 0)
        torque /= size;
    mutex.give();
    return torque;
}

int MotorGroup::get_voltage()
{
    int voltage = 0;
    mutex.take();
    for (int i = 0; i < size; i++)
        voltage += motors[i].get_voltage();
    if (size != 0)
        voltage /= size;
    mutex.give();
    return voltage;
}

int MotorGroup::get_zero_position_flag()
{
    mutex.take();
    int flag = motors[0].get_zero_position_flag();
    mutex.give();
    return flag;
}

bool MotorGroup::is_stopped()
{
    mutex.take();
    bool stopped = motors[0].is_stopped();
    mutex.give();
    return stopped;
}

bool MotorGroup::is_over_current()
{
    mutex.take();
    bool over = motors[0].is_over_current();
    mutex.give();
    return over;
}

bool MotorGroup::is_over_temp()
{
    mutex.take();
    bool over = motors[0].is_over_temp();
    mutex.give();
    return over;
}

pros::motor_brake_mode_e_t MotorGroup::get_brake_mode()
{
    mutex.take();
    pros::motor_brake_mode_e_t brake_mode = motors[0].get_brake_mode();
    mutex.give();
    return brake_mode;
}

int MotorGroup::get_current_limit()
{
    mutex.take();
    int limit = motors[0].get_current_limit();
    mutex.give();
    return limit;
}

pros::motor_encoder_units_e_t MotorGroup::get_encoder_units()
{
    mutex.take();
    pros::motor_encoder_units_e_t encoder_units = motors[0].get_encoder_units();
    mutex.give();
    return encoder_units;
}

pros::motor_gearset_e_t MotorGroup::get_gearing()
{
    mutex.take();
    pros::motor_gearset_e_t gearing = motors[0].get_gearing();
    mutex.give();
    return gearing;
}

int MotorGroup::get_voltage_limit()
{
    mutex.take();
    int limit = motors[0].get_voltage_limit();
    mutex.give();
    return limit;
}

void MotorGroup::set_brake_mode(pros::motor_brake_mode_e_t mode)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].set_brake_mode(mode);
    mutex.give();
}

void MotorGroup::set_current_limit(int limit)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].set_current_limit(limit);
    mutex.give();
}

void MotorGroup::set_encoder_units(pros::motor_encoder_units_e_t units)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].set_encoder_units(units);
    mutex.give();
}

void MotorGroup::set_gearing(pros::motor_gearset_e_t gearset)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].set_gearing(gearset);
    mutex.give();
}

void MotorGroup::set_voltage_limit(int limit)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].set_voltage_limit(limit);
    mutex.give();
}

void MotorGroup::set_zero_position(double position)
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].set_zero_position(position);
    mutex.give();
}

void MotorGroup::tare_position()
{
    mutex.take();
    for (int i = 0; i < size; i++)
        motors[i].tare_position();
    mutex.give();
}

MotorGroup& MotorGroup::operator=(const MotorGroup& rhs)
{
    mutex.take();
    for (int i = 0; i < rhs.size; i++)
        motors[i] = rhs.motors[i];
    size = rhs.size;
    mutex.give();
    return *this;
}