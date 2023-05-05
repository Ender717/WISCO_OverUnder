// Included headers
#include "devices/InertialSensor.h"
#include "pros/imu.h"

InertialSensor::InertialSensor()
{
    port = 0;
}

InertialSensor::InertialSensor(uint8_t _port) : port(_port)
{
    
}

InertialSensor::InertialSensor(const InertialSensor& copy) : port(copy.port)
{

}

void InertialSensor::set_port(uint8_t _port)
{
    mutex.take();
    port = _port;
    mutex.give();
}

uint8_t InertialSensor::get_port()
{
    mutex.take();
    uint8_t result = port;
    mutex.give();
    return result;
}

int InertialSensor::reset(bool blocking)
{
    int result = PROS_ERR;
    mutex.take();
    while (pros::c::imu_get_status(port) == pros::c::E_IMU_STATUS_CALIBRATING)
        pros::delay(50);
    if (blocking)
        result = pros::c::imu_reset_blocking(port);
    else
        result = pros::c::imu_reset(port);
    mutex.give();
    return result;
}

double InertialSensor::get_rotation()
{
    mutex.take();
    double rotation = pros::c::imu_get_rotation(port);
    mutex.give();
    return rotation;
}

double InertialSensor::get_heading()
{
    mutex.take();
    double heading = pros::c::imu_get_heading(port);
    mutex.give();
    return heading;
}

pros::c::quaternion_s_t InertialSensor::get_quaternion()
{
    mutex.take();
    pros::c::quaternion_s_t quaternion = pros::c::imu_get_quaternion(port);
    mutex.give();
    return quaternion;
}

pros::c::euler_s_t InertialSensor::get_euler()
{
    mutex.take();
    pros::c::euler_s_t euler = pros::c::imu_get_euler(port);
    mutex.give();
    return euler;
}

double InertialSensor::get_pitch()
{
    mutex.take();
    double pitch = pros::c::imu_get_pitch(port);
    mutex.give();
    return pitch;
}

double InertialSensor::get_roll()
{
    mutex.take();
    double roll = pros::c::imu_get_roll(port);
    mutex.give();
    return roll;
}

double InertialSensor::get_yaw()
{
    mutex.take();
    double yaw = pros::c::imu_get_yaw(port);
    mutex.give();
    return yaw;
}

pros::c::imu_gyro_s_t InertialSensor::get_gyro_rate()
{
    mutex.take();
    pros::c::imu_gyro_s_t gyro_rate = pros::c::imu_get_gyro_rate(port);
    mutex.give();
    return gyro_rate;
}

pros::c::imu_accel_s_t InertialSensor::get_accel()
{
    mutex.take();
    pros::c::imu_accel_s_t accel = pros::c::imu_get_accel(port);
    mutex.give();
    return accel;
}

pros::c::imu_status_e_t InertialSensor::get_status()
{
    mutex.take();
    pros::c::imu_status_e_t status = pros::c::imu_get_status(port);
    mutex.give();
    return status;
}

int InertialSensor::tare_heading()
{
    mutex.take();
    int result = pros::c::imu_tare_heading(port);
    mutex.give();
    return result;
}

int InertialSensor::tare_rotation()
{
    mutex.take();
    int result = pros::c::imu_tare_rotation(port);
    mutex.give();
    return result;
}

int InertialSensor::tare_pitch()
{
    mutex.take();
    int result = pros::c::imu_tare_pitch(port);
    mutex.give();
    return result;
}

int InertialSensor::tare_roll()
{
    mutex.take();
    int result = pros::c::imu_tare_roll(port);
    mutex.give();
    return result;
}

int InertialSensor::tare_yaw()
{
    mutex.take();
    int result = pros::c::imu_tare_yaw(port);
    mutex.give();
    return result;
}

int InertialSensor::tare_euler()
{
    mutex.take();
    int result = pros::c::imu_tare_euler(port);
    mutex.give();
    return result;
}

int InertialSensor::tare()
{
    mutex.take();
    int result = pros::c::imu_tare(port);
    mutex.give();
    return result;
}

int InertialSensor::set_euler(pros::c::euler_s_t euler)
{
    mutex.take();
    int result = pros::c::imu_set_euler(port, euler);
    mutex.give();
    return result;
}

int InertialSensor::set_rotation(double rotation)
{
    mutex.take();
    int result = pros::c::imu_set_rotation(port, rotation);
    mutex.give();
    return result;
}

int InertialSensor::set_heading(double heading)
{
    mutex.take();
    int result = pros::c::imu_set_heading(port, heading);
    mutex.take();
    return result;
}

int InertialSensor::set_pitch(double pitch)
{
    mutex.take();
    int result = pros::c::imu_set_pitch(port, pitch);
    mutex.give();
    return result;
}

int InertialSensor::set_roll(double roll)
{
    mutex.take();
    int result = pros::c::imu_set_roll(port, roll);
    mutex.give();
    return result;
}

int InertialSensor::set_yaw(double yaw)
{
    mutex.take();
    int result = pros::c::imu_set_yaw(port, yaw);
    mutex.give();
    return result;
}

InertialSensor& InertialSensor::operator=(const InertialSensor& rhs)
{
    mutex.take();
    port = rhs.port;
    mutex.give();
    return *this;
}