// Inclusion guard
#ifndef MOTOR_GROUP_H
#define MOTOR_GROUP_H

// Included headers
#include "main.h"
#include "Motor.h"
#include "utils/Utilities.h"

/**
 * This class manages a group of motors
 * @author Nathan Sandvig
 */
class MotorGroup
{
private:
    /**
     * The maximum size of the motor group
     */
    static constexpr int MAX_SIZE = 5;

    /**
     * The mutex to keep the motor group threadsafe
     */
    pros::Mutex mutex;

    /**
     * The motors in the motor group
     */
    Motor motors[MAX_SIZE];

    /**
     * The current size of the motor group
     */
    int size;

public:
    /**
     * Default constructor
     */
    MotorGroup();

    /**
     * Copy constructor
     * @param copy The motor group being copied
     */
    MotorGroup(const MotorGroup& copy);

    /**
     * Adds a motor to the group
     * @param motor The motor being added
     */
    void add_motor(Motor& motor);

    /**
     * Gets the size of the motor group
     * @return The size of the motor group
     */
    int get_size();

    /**
     * Gets the list of ports for the motors
     * @return The list of ports for the motors
     */
    uint8_t* get_ports();

    /**
     * Moves the motors with the analog input power
     * @param power The power to move the motors with
     */
    void move(double power);

    /**
     * Moves the motors to an absolute position at a set velocity
     * @param position The target position
     * @param velocity The velocity to move with
     */
    void move_absolute(double position, double velocity);

    /**
     * Moves the motors to a relative position at a set velocity
     * @param position The target position
     * @param velocity The velocity to move with
     */
    void move_relative(double position, double velocity);

    /**
     * Moves the motors at a set RPM
     * @param velocity The target RPM
     */
    void move_velocity(double velocity);

    /**
     * Moves the motors with an input voltage
     * @param voltage The input voltage
     */
    void move_voltage(double voltage);

    /**
     * Activates the brakes on the motors
     */
    void brake();

    /**
     * Modifies the velocity for a profiled movement
     * @param velocity The new velocity
     */
    void modify_profiled_velocity(double velocity);

    /**
     * Gets the target position for a profiled movement
     * @return The target position
     */
    double get_target_position();

    /**
     * Gets the target velocity for a profiled movement
     * @return The target velocity
     */
    int get_target_velocity();

    /**
     * Gets the actual velocity of the motors
     * @return The actual velocity of the motors
     */
    double get_actual_velocity();

    /**
     * Gets the current draw of the motors
     * @return The current draw of the motors
     */
    int get_current_draw();

    /**
     * Gets the direction of the motors
     * @return 1 if the motors are moving forward, -1 if backward
     */
    int get_direction();

    /**
     * Gets the efficiency of the motors
     * @return The efficiency of the motors
     */
    int get_efficiency();

    /**
     * Gets the faults of the motors
     * @return The motor faults
     */
    int get_faults();

    /**
     * Gets the flags of the motors
     * @return The motor flags
     */
    int get_flags();

    /**
     * Gets the position of the motors
     * @return The position of the motors
     */
    double get_position();

    /**
     * Gets the power of the motors
     * @return The power of the motors
     */
    double get_power();

    /**
     * Gets the raw position of the motors at a given timestamp
     * @param timestamp The timestamp to fetch the position from
     * @return The raw position of the motors at a given timestamp
     */
    int get_raw_position(uint32_t* timestamp);

    /**
     * Gets the temperature of the motors
     * @return The temperature of the motors
     */
    double get_temperature();

    /**
     * Gets the torque of the motors
     * @return The torque of the motors
     */
    double get_torque();

    /**
     * Gets the voltage of the motors
     * @return The voltage of the motors
     */
    int get_voltage();

    /**
     * Checks if the motors are at the zero position
     * @return The zero position flag of the motors
     */
    int get_zero_position_flag();

    /**
     * Checks if the motors are stopped
     * @return True if the motors are stopped, false if not
     */
    bool is_stopped();

    /**
     * Checks if the motors are over current
     * @return True if the motors are over current, false if not
     */
    bool is_over_current();

    /**
     * Checks if the motors are over temp
     * @return True if the motors are over temp, false if not
     */
    bool is_over_temp();

    /**
     * Gets the brake mode of the motors
     * @return The brake mode of the motors
     */
    pros::motor_brake_mode_e_t get_brake_mode();

    /**
     * Gets the current limit of the motors
     * @return The current limit of the motors
     */
    int get_current_limit();

    /**
     * Gets the encoder units of the motors
     * @return The encoder units of the motors
     */
    pros::motor_encoder_units_e_t get_encoder_units();

    /**
     * Gets the gearing of the motors
     * @return The gearing of the motors
     */
    pros::motor_gearset_e_t get_gearing();

    /**
     * Gets the voltage limit of the motors
     * @return The voltage limit of the motors
     */
    int get_voltage_limit();

    /**
     * Sets the brake mode of the motors
     * @param mode The brake mode
     */
    void set_brake_mode(pros::motor_brake_mode_e_t mode);

    /**
     * Sets the current limit for the motors
     * @param limit The current limit
     */
    void set_current_limit(int limit);

    /**
     * Sets the encoder units for the motors
     * @param units The encoder units
     */
    void set_encoder_units(pros::motor_encoder_units_e_t units);

    /**
     * Sets the gearing for the motors
     * @param gearset The gearset
     */
    void set_gearing(pros::motor_gearset_e_t gearset);

    /**
     * Sets the voltage limit for the motors
     * @param limit The voltage limit
     */
    void set_voltage_limit(int limit);

    /**
     * Sets the zero position for the motors
     * @param position The new zero position
     */
    void set_zero_position(double position);

    /**
     * Resets the motors' positions to absolute 0
     */
    void tare_position();

    /**
     * Assignment operator overload
     * @param rhs The MotorGroup on the right hand side of the operator
     * @return This MotorGroup with the assigned values
     */
    MotorGroup& operator=(const MotorGroup& rhs);
};

#endif