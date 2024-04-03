#ifndef WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_I_ELEVATOR_HPP
#define WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_I_ELEVATOR_HPP

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
 * @brief Namespace for elevator classes
 * @author Nathan Sandvig
 * 
 */
namespace elevator
{

/**
 * @brief Interface for elevators
 * @author Nathan Sandvig
 * 
 */
class IElevator
{
public:
    /**
     * @brief Destroy the IElevator object
     * 
     */
    virtual ~IElevator() = default;

    /**
     * @brief Initializes the elevator
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the elevator
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Get the position of the elevator in inches
     * 
     * @return double The elevator position in inches
     */
    virtual double getPosition() = 0;

    /**
     * @brief Set the position of the elevator in inches
     * 
     * @param position The elevator position in inches
     */
    virtual void setPosition(double position) = 0;
};
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif