#ifndef WISCO_ROBOT_SUBSYSTEMS_INTAKE_I_INTAKE_HPP
#define WISCO_ROBOT_SUBSYSTEMS_INTAKE_I_INTAKE_HPP

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
 * @brief Namespace for intake classes
 * @author Nathan Sandvig
 * 
 */
namespace intake
{

/**
 * @brief Interface for intakes
 * @author Nathan Sandvig
 * 
 */
class IIntake
{
public:
    /**
     * @brief Destroy the IIntake object
     * 
     */
    virtual ~IIntake() = default;

    /**
     * @brief Initializes the intake
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the intake
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Get the velocity of the intake in in/s
     * 
     * @return double The intake velocity
     */
    virtual double getVelocity() = 0;

    /**
     * @brief Set the velocity of the intake
     * 
     * @param velocity The velocity of the intake in in/s
     */
    virtual void setVelocity(double velocity) = 0;

    /**
     * @brief Set the voltage of the intake directly
     * 
     * @param voltage The voltage for the intake
     */
    virtual void setVoltage(double voltage) = 0;
};
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif