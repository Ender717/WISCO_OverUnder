#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_I_DIFFERENTIAL_DRIVE_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_I_DIFFERENTIAL_DRIVE_HPP

#include "Velocity.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief The namespace that holds all robot classes
 * @author Nathan Sandvig
 *
 */
namespace robot
{

/**
 * @brief Namespace for all robot subsystems
 * @author Nathan Sandvig
 * 
 */
namespace subsystems
{

/**
 * @brief Namespace for drive classes
 * @author Nathan Sandvig
 * 
 */
namespace drive
{

/**
 * @brief Interface for differential drivetrains
 * @author Nathan Sandvig
 * 
 */
class IDifferentialDrive
{
public:
    /**
     * @brief Destroy the IDifferentialDrive object
     * 
     */
    virtual ~IDifferentialDrive() = default;

    /**
     * @brief Initializes the differential drive
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the differential drive
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Get the velocity values of the drive
     * 
     * @return double The drive velocity
     */
    virtual Velocity getVelocity() = 0;

    /**
     * @brief Set the velocity values of the drive
     * 
     * @param velocity The velocity values for the drive
     */
    virtual void setVelocity(Velocity velocity) = 0;

    /**
     * @brief Set the voltages of the drive directly
     * 
     * @param left_voltage The voltage for the left side of the drive
     * @param right_voltage The voltage for the right side of the drive
     */
    virtual void setVoltage(double left_voltage, double right_voltage) = 0;
};
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif