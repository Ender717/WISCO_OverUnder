// Inclusion guard
#ifndef ROTATION_SENSOR_H
#define ROTATION_SENSOR_H

// Included headers
#include "main.h"
#include "utils/Utilities.h"

/**
 * This class runs a rotation sensor device wrapper
 * @author Nathan Sandvig
 */
class RotationSensor
{
private:
    /**
     * The mutex for the rotation sensor
     */
    pros::Mutex mutex;

    /**
     * The port for the rotation sensor
     */
    uint8_t port;

public:
    /**
     * Default constructor
     */
    RotationSensor();

    /**
     * Parameterized constructor
     * @param _port The port for the sensor
     * @param _reversed Whether the sensor is reversed or not, false by default
     */
    RotationSensor(uint8_t _port, bool _reversed = false);

    /**
     * Copy constructor
     * @param copy The rotation sensor wrapper being copied
     */
    RotationSensor(const RotationSensor& copy);

    /**
     * Sets the port of the rotation sensor
     * @param _port The new port
     */
    void set_port(uint8_t _port);

    /**
     * Gets the port of the rotation sensor
     * @return The port
     */
    uint8_t get_port();

    /**
     * Resets the absolute position of the rotation sensor
     * @return ENXIO if port is invalid, ENODEV if type is incorrect
     */
    int reset();

    /**
     * Sets the rotation sensor to a desired rotation value
     * @return ENXIO if port is invalid, ENODEV if type is incorrect
     */
    int set_position(uint32_t position);

    /**
     * Resets the relative position of the rotation sensor to 0
     * @return ENXIO if port is invalid, ENODEV if type is incorrect
     */
    int reset_position();

    /**
     * Gets the current position of the rotation sensor
     * @return Rotation sensor position in centidegrees if valid,
     *         ENXIO if port is invalid, ENODEV if type is incorrect
     */
    int get_position();

    /**
     * Gets the current velocity of the rotation sensor in centidegrees per second
     * @return Rotation sensor velocity in centidegrees per second if valid,
     *         ENXIO if port is invalid, ENODEV if type is incorrect
     */
    int get_velocity();

    /**
     * Gets the current angle of the rotation sensor
     * @return Rotation sensor angle in centidegrees (0-36000) if valid,
     *         ENXIO if port is invalid, ENODEV if type is incorrect
     */
    int get_angle();

    /**
     * Sets the reversal flag of the rotation sensor to the desired value
     * @param _reversed The new value for the reversal flag
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_reversed(bool _reversed);

    /**
     * Reversed the current direction of the rotation sensor
     * @return ENXIO if port is invalid, ENODEV if type is incorrect
     */
    int reverse();

    /**
     * Get the rotation sensor's reversal flag
     * @return Boolean value of the reversal flag if valid, PROS_ERR if the operation failed
     */
    int get_reversed();

    /**
     * Sets the rotation sensor's refresh interval in milliseconds
     * @param rate The new data rate in milliseconds
     * @return ENXIO if port is invalid, ENODEV if type is incorrect
     */
    int set_data_rate(uint32_t rate);

    /**
     * Assignment operator override
     * @param rhs The RotationSensor object on the right hand side of the operator
     * @return This RotationSensor object with the assigned values
     */
    RotationSensor& operator=(const RotationSensor& rhs);
};

#endif