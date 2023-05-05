// Inclusion guard
#ifndef PISTON_H
#define PISTON_H

// Included headers
#include "main.h"

/**
 * This class manages a piston wrapper
 * @author Nathan Sandvig
 */
class Piston
{
private:
    /**
     * The mutex to keep the piston thread-safe
     */
    pros::Mutex mutex;

    /**
     * The port for this piston
     */
    uint8_t port;

    /**
     * The port for the 3-wire expander (optional)
     */
    uint8_t ext_port;

    /**
     * Whether the piston is toggled or not
     */
    bool toggled;

public:
    /**
     * Default constructor
     */
    Piston();

    /**
     * Parameterized constructor
     * @param _port The port for the piston
     * @param _ext_port The port for the 3-wire expander (optional)
     */
    Piston(uint8_t _port, uint8_t _ext_port = 0);

    /**
     * Copy constructor
     * @param copy The Piston object being copied
     */
    Piston(const Piston& copy);

    /**
     * Sets the port of the piston
     * @param _port The new port
     * @param _ext_port The new smart port (optional)
     */
    void set_port(uint8_t _port, uint8_t _ext_port);

    /**
     * Gets the current port of the piston
     * @return The piston's current port
     */
    uint8_t get_port();

    /**
     * Gets the port of the 3-wire expander
     * @return The piston's 3-wire expander port
     */
    uint8_t get_ext_port();

    /**
     * Toggles the piston
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int toggle();

    /**
     * Sets the piston's toggled state
     * @param _toggled The new toggled state
     * @return 1 if the operation was successful, PROS_ERR if the operation failed
     */
    int set_toggled(bool _toggled);

    /**
     * Checks if the piston is toggled
     * @return True if the piston is toggled, false if not
     */
    bool get_toggled();

    /**
     * Assignment operator overload
     * @param rhs The Piston object on the right hand side of the operator
     * @return This Piston object with the assigned values
     */
    Piston& operator=(const Piston& rhs);
};

#endif