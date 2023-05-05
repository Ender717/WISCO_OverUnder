// Inclusion guard
#ifndef PISTON_GROUP_H
#define PISTON_GROUP_H

// Included headers
#include "main.h"
#include "Piston.h"

/**
 * This class manages a group of pistons
 * @author Nathan Sandvig
 */
class PistonGroup
{
private:
    /**
     * The maximum size of a piston group
     */
    static constexpr int MAX_SIZE = 5;

    /**
     * The mutex to keep the Piston group threadsafe
     */
    pros::Mutex mutex;

    /**
     * The pistons in the group
     */
    Piston pistons[MAX_SIZE];

    /**
     * The current size of the group
     */
    int size;

public:
    /**
     * Default constructor
     */
    PistonGroup();

    /**
     * Copy constructor
     * @param copy The PistonGroup being copied
     */
    PistonGroup(const PistonGroup& copy);

    /**
     * Adds a piston to the group
     * @param piston The piston
     */
    void add_piston(Piston& piston);

    /**
     * Gets the size of the piston group
     * @return The size of the group
     */
    int get_size();

    /**
     * Gets the ports of the pistons in the group
     * @return The ports of the pistons
     */
    uint8_t* get_ports();

    /**
     * Toggles the pistons
     */
    void toggle();

    /**
     * Sets the toggled state of the pistons
     * @param value The new toggled state
     */
    void set_toggled(bool value);

    /**
     * Checks if the pistons are toggled
     * @return True if the pistons are toggled, false if not
     */
    bool get_toggled();

    /**
     * Assignment operator overload
     * @param rhs The PistonGroup on the right hand side of the operator
     * @return This PistonGroup with the assigned values
     */
    PistonGroup& operator=(const PistonGroup& rhs);
};

#endif