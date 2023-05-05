// Inclusion guard
#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H

// Included headers
#include "main.h"

/**
 * This class manages an analog input device wrapper
 * @author Nathan Sandvig
 */
class AnalogInput
{
private:
    /**
     * The mutex to keep this AnalogInput device thread-safe
     */
    pros::Mutex mutex;

    /**
     * The port for the analog input
     */
    uint8_t port;

    /**
     * The port for the 3-wire extender for this device, if applicable
     */
    uint8_t ext_port;

public:
    /**
     * Default constructor
     */
    AnalogInput();

    /**
     * Parameterized constructor
     * @param _port The port for the analog input device
     * @param _ext_port The port for the 3-wire extender (optional)
     */
    AnalogInput(uint8_t _port, uint8_t _ext_port = 0);

    /**
     * Copy constructor
     * @param copy The AnalogInput object being copied
     */
    AnalogInput(const AnalogInput& copy);

    /**
     * Sets the port of the analog input device
     * @param _port The new port
     * @param _ext_port The new 3-wire extender port (optional)
     */
    void set_port(uint8_t _port, uint8_t _ext_port = 0);

    /**
     * Gets the port of the analog input device
     * @return The device's port
     */
    uint8_t get_port();

    /**
     * Gets the port of the 3-wire extender this device is connected to
     * @return The 3-wire extender's port
     */
    uint8_t get_ext_port();

    /**
     * Calibrates the analog input device
     * @return The average sensor value the device calibrated to
     */
    int calibrate();

    /**
     * Gets the analog input device's input value
     * @return The input value (0 - 4095)
     */
    int get_value();

    /**
     * Gets the analog input device's input value relative to the calibrated value
     * @return The calibrated input value (-4095 - 4095)
     */
    int get_value_calibrated();

    /**
     * Gets the analog input device's calibrated input value in high resolution
     * @return The high-resolution calibrated input value (-16384 - 16384)
     */
    int get_value_calibrated_HR();

    /**
     * Assignment operator overload
     * @param rhs The AnalogInput object on the right hand side of the operator
     * @return This AnalogInput object with the assigned values
     */
    AnalogInput& operator=(const AnalogInput& rhs);
};

#endif