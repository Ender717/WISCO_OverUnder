#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_I_DIFFERENTIAL_DRIVE_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_I_DIFFERENTIAL_DRIVE_HPP

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
     * @brief Get the velocity of the left side of the drive
     * 
     * @return double The left drive velocity
     */
    virtual double getLeftVelocity() = 0;

    /**
     * @brief Get the velocity of the right side of the drive
     * 
     * @return double The right drive velocity
     */
    virtual double getRightVelocity() = 0;

    /**
     * @brief Set the acceleration values of the drive
     * 
     * @param left_acceleration The acceleration of the left side of the drive
     * @param right_acceleration The acceleration of the right side of the drive
     */
    virtual void setAcceleration(double left_acceleration, double right_acceleration) = 0;
};
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif