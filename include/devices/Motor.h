// Inclusion guard
#ifndef MOTOR_H
#define MOTOR_H

// Included headers
#include "main.h"
#include "pros/motors.h"
#include "utils/Utilities.h"

/**
 * This class manages a motor wrapper
 * @author Nathan Sandvig
 */
class Motor
{
private:
    /**
     * The mutex to keep the motor threadsafe
     */
    pros::Mutex mutex;

    /**
     * The port for the motor
     */
    uint8_t port;

    /**
     * Gets the capped analog voltage form of an input power
     * @param power The input power
     * @return The capped analog voltage
     */
    int getAnalogVoltage(double power);

    /**
     * Gets the capped velocity form of an input velocity
     * @param velocity The input velocity
     * @return The capped velocity
     */
    int getVelocity(double velocity);

    /**
     * Gets the capped voltage form of an input voltage
     * @param voltage The input voltage
     * @return The capped voltage
     */
    int getVoltage(double voltage);

public:
    /**
     * Default constructor
     */
    Motor();

    /**
     * Parameterized constructor
     * @param _port The port for the motor
     * @param gearset The gearset for the motor, 200rpm by default
     * @param reversed Whether or not the motor should be reversed, false by default
     * @param units The encoder units for the motor, encoder counts by default
     */
    Motor(uint8_t _port, pros::motor_gearset_e_t gearset = pros::E_MOTOR_GEAR_200, bool reversed = false, pros::motor_encoder_units_e_t units = pros::E_MOTOR_ENCODER_COUNTS);

    /**
     * Copy constructor
     * @param copy The motor being copied
     */
    Motor(const Motor& copy);

    /**
     * Sets the port of the motor
     * @param _port The new port number
     */
    void set_port(uint8_t _port);

    /**
     * Gets the port of the motor
     * @return The port number
     */
    uint8_t get_port();

    /**
     * Moves the motor using analog controls
     * @param power The power level from -127 to 127
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int move(double power);

    /**
     * Moves the motor to an absolute position at a set velocity - not blocking
     * @param position The new absolute position
     * @param velocity The velocity in RPM
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int move_absolute(double position, double velocity);

    /**
     * Moves the motor to a relative position at a set velocity - not blocking
     * @param position The new position relative to current
     * @param velocity The velocity in RPM
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int move_relative(double position, double velocity);

    /**
     * Moves the motor at a set RPM
     * @param velocity The new motor velocity in RPM
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int move_velocity(double velocity);

    /**
     * Moves the motor using a set voltage in millivolts
     * @param voltage The new voltage from -12000 to 12000
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int move_voltage(double voltage);

    /**
     * Sets the motor velocity to zero and activates the brake mode
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int brake();

    /**
     * Changes the target velocity for a profiled movement
     * @param velocity The new motor velocity in RPM
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int modify_profiled_velocity(double velocity);

    /**
     * Gets the target position for a profiled movement
     * @return The target position, PROS_ERR_F if the operation failed
     */
    double get_target_position();

    /**
     * Gets the target velocity for a profiled movement
     * @return The target velocity, PROS_ERR if the operation failed
     */
    int get_target_velocity();

    /**
     * Gets the actual RPM of the motor
     * @return The motor's velocity in RPM, PROS_ERR_F if the operation failed
     */
    double get_actual_velocity();

    /**
     * Gets the current draw from the motor in mA
     * @return The motor's current in mA, PROS_ERR if the operation failed
     */
    int get_current_draw();

    /**
     * Gets the direction of movement of the motor
     * @return 1 for forward movement, -1 for backward movement, PROS_ERR if the operation failed
     */
    int get_direction();

    /**
     * Gets the efficiency percentage of the motor
     * @return The efficiency of the motor, PROS_ERR if the operation failed
     */
    int get_efficiency();

    /**
     * Gets the faults experienced by the motor
     * @return The faults of the motor
     */
    unsigned int get_faults();

    /**
     * Gets the flags set by the motor's operation
     * @return The flags from the motor
     */
    unsigned int get_flags();

    /**
     * Gets the absolute position of the motor
     * @return The motor's absolute position, PROS_ERR_F if the operation failed
     */
    double get_position();

    /**
     * Gets the power drawn by the motor in Watts
     * @return The power draw of the motor in Watts, PROS_ERR_F if the operation failed
     */
    double get_power();

    /**
     * Gets the raw encoder count of the motor at a specific timestamp
     * @param timestamp The timestamp to fetch the encoder position from
     * @return The raw encoder count, PROS_ERR if the operation failed
     */
    int get_raw_position(uint32_t* timestamp);

    /**
     * Gets the temperature of the motor in Celcius
     * @return The temperature of the motor, PROS_ERR_F if the operation failed
     */
    double get_temperature();

    /**
     * Gets the torque generated by the motor in Nm
     * @return The torque from the motor, PROS_ERR_F if the operation failed
     */
    double get_torque();

    /**
     * Gets the voltage sent to the motor in mV
     * @return The voltage sent, PROS_ERR if the operation failed
     */
    int get_voltage();

    /**
     * Gets the zero position flag for the motor
     * @return 1 if the motor is at 0 absolute, 0 if not, PROS_ERR if the operation failed
     */
    int get_zero_position_flag();

    /**
     * Gets the zero velocity flag for the motor
     * @return 1 if the motor is not moving, 0 if moving, PROS_ERR if the operation failed
     */
    int is_stopped();

    /**
     * Checks if the motor is drawing more than its current limit
     * @return 1 if the motor is over limit, 0 if not, PROS_ERR if the operation failed
     */
    int is_over_current();

    /**
     * Checks if the motor is over temp
     * @return 1 if the motor is over temp, 0 if not, PROS_ERR if the operation failed
     */
    int is_over_temp();

    /**
     * Gets the motor's brake mode
     * @return The brake mode of the motor, E_MOTOR_BRAKE_INVALID if the operation failed
     */
    pros::motor_brake_mode_e_t get_brake_mode();

    /**
     * Gets the motor's current limit in mA
     * @return The motor's current limit, PROS_ERR if the operation failed
     */
    int get_current_limit();

    /**
     * Gets the motor's encoder units
     * @return The motor's encoder units, E_MOTOR_ENCODER_INVALID if the operation failed
     */
    pros::motor_encoder_units_e_t get_encoder_units();

    /**
     * Gets the gearset of the motor
     * @return The motor's gearset, E_GEARSET_INVALID if the operation failed
     */
    pros::motor_gearset_e_t get_gearing();

    /**
     * Gets the motor's voltage limit in V
     * @return The motor's voltage limit in V, PROS_ERR if the operation failed
     */
    int get_voltage_limit();

    /**
     * Checks if the motor is reversed
     * @return 1 if the motor is reversed, 0 if not, PROS_ERR if the operation failed
     */
    int is_reversed();

    /**
     * Sets the brake mode of the motor
     * @param mode The new brake mode
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_brake_mode(pros::motor_brake_mode_e_t mode);

    /**
     * Sets the motor's current limit in mA
     * @param limit The new current limit
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_current_limit(int limit);

    /**
     * Sets the motor's encoder units
     * @param units The new encoder units
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_encoder_units(pros::motor_encoder_units_e_t units);

    /**
     * Sets the motor's gearset
     * @param gearset The new gearset
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_gearing(pros::motor_gearset_e_t gearset);

    /**
     * Sets the motor's reversal flag
     * @param reversed Whether or not the motor should be reversed
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_reversed(bool reversed);

    /**
     * Sets the motor's voltage limit in mV
     * @param limit The new voltage limit
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_voltage_limit(int limit);

    /**
     * Sets the motor's zero position
     * @param position The new zero position
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_zero_position(double position);

    /**
     * Sets the motor's absolute zero position to its current position
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int tare_position();

    /**
     * Assignment operator overload
     * @param rhs The Motor object on the right hand side of the operator
     * @return This Motor object with the assigned values
     */
    Motor& operator=(const Motor& rhs);
};

#endif