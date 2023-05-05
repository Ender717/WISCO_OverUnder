// Inclusion guard
#ifndef INERTIAL_SENSOR_H
#define INERTIAL_SENSOR_H

// Included headers
#include "main.h"
#include "utils/Utilities.h"

/**
 * This class handles an inertial sensor wrapper
 * @author Nathan Sandvig
 */
class InertialSensor
{
private:
    /**
     * The mutex for the inertial sensor
     */
    pros::Mutex mutex;

    /**
     * The port of the inertial sensor
     */
    uint8_t port;

public:
    /**
     * Default constructor
     */
    InertialSensor();

    /**
     * Parameterized constructor
     * @param port The port for the inertial sensor
     */
    InertialSensor(uint8_t _port);

    /**
     * Copy constructor
     * @param copy The InertialSensor object being copied
     */
    InertialSensor(const InertialSensor& copy);

    /**
     * Sets the port of the inertial sensor
     * @param _port The new port
     */
    void set_port(uint8_t _port);

    /**
     * Gets the port of the inertial sensor
     * @return The port
     */
    uint8_t get_port();

    /**
     * Calibrates the inertial sensor
     * @return 1 if successful, PROS_ERR if the operation failed
     */
    int reset(bool blocking = false);

    /**
     * Gets the total number of degrees rotated CCW about the z-axis
     * @return The rotation of the inertial sensor if successful,
     *         PROS_ERR_F if the operation failed
     */
    double get_rotation();

    /**
     * Gets the inertial sensor heading CCW about the z-axis relative to initial position
     * @return The heading of the inertial sensor if successful,
     *         PROS_ERR_F if the operation failed
     */
    double get_heading();

    /**
     * Gets the quaternion representing the inertial sensor's orientation
     * @return The inertial sensor's orientation quaternion if successful,
     *         A quaternion filled with PROS_ERR_F if the operation failed
     */
    pros::c::quaternion_s_t get_quaternion();

    /**
     * Gets the Euler angles representing the inertial sensor's orientation
     * @return The inertial sensor's orientation Euler angles if successful,
     *         A Euler struct filled with PROS_ERR_F if the operation failed
     */
    pros::c::euler_s_t get_euler();

    /**
     * Gets the pitch of the inertial sensor (-180, 180)
     * @return The pitch angle if successful, PROS_ERR_F if the operation failed
     */
    double get_pitch();

    /**
     * Gets the roll of the inertial sensor (-180, 180)
     * @return The roll angle if successful, PROS_ERR_F if the operation failed
     */
    double get_roll();

    /**
     * Gets the yaw of the inertial sensor (-180, 180)
     * @return The yaw angle if successful, PROS_ERR_F if the operation failed
     */
    double get_yaw();

    /**
     * Gets the inertial sensor's raw gyroscopic values
     * @return The raw gyroscopic values if successful,
     *         A gryoscopic value struct filled with PROS_ERR_F if the operation failed
     */
    pros::c::imu_gyro_s_t get_gyro_rate();

    /**
     * Gets the inertial sensor's raw acceleration values
     * @return The raw acceleration values if successful,
     *         An acceleration value struct filled with PROS_ERR_F if the operation failed
     */
    pros::c::imu_accel_s_t get_accel();

    /**
     * Gets the status of the inertial sensor
     * @return The status of the inertial sensor if successful, PROS_ERR if not
     */
    pros::c::imu_status_e_t get_status();

    /**
     * Resets the inertial sensor's current heading to 0
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int tare_heading();

    /**
     * Resets the inertial sensor's current rotation to 0
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int tare_rotation();

    /**
     * Resets the inertial sensor's current pitch to 0
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int tare_pitch();

    /**
     * Resets the inertial sensor's current roll to 0
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int tare_roll();

    /**
     * Resets the inertial sensor's current yaw to 0
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int tare_yaw();

    /**
     * Resets the inertial sensor's 3 Euler values to 0
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int tare_euler();

    /**
     * Resets all values of the inertial sensor to 0
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int tare();

    /**
     * Sets the euler values of the inertial sensor
     * @param euler The new euler values
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_euler(pros::c::euler_s_t euler);

    /**
     * Sets the rotation value of the inertial sensor
     * @param rotation The new rotation value
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_rotation(double rotation);

    /**
     * Sets the heading value of the inertial sensor
     * @param heading The new heading value
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_heading(double heading);

    /**
     * Sets the pitch value of the inertial sensor
     * @param pitch The new pitch value
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_pitch(double pitch);

    /**
     * Sets the roll value of the inertial sensor
     * @param roll The new roll value
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_roll(double roll);

    /**
     * Sets the yaw value of the inertial sensor
     * @param yaw The new yaw value
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_yaw(double yaw);

    /**
     * Assignment operator overload
     * @param rhs The InertialSensor object on the right hand side of the operator
     * @return This InertialSensor object filled with the assigned values
     */
    InertialSensor& operator=(const InertialSensor& rhs);
};

#endif