#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_I_CLAW_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_I_CLAW_HPP

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
 * @brief Namespace for hang classes
 * @author Nathan Sandvig
 * 
 */
namespace hang
{

/**
 * @brief Interface for claws with an open and closed position
 * @author Nathan Sandvig
 * 
 */
class IClaw
{
public:
    /**
     * @brief Destroy the IClaw object
     * 
     */
    virtual ~IClaw() = default;

    /**
     * @brief Initializes the claw
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the claw
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Closes the claw
     * 
     */
    virtual void close() = 0;

    /**
     * @brief Opens the claw
     * 
     */
    virtual void open() = 0;

    /**
     * @brief Checks if the claw is closed
     * 
     * @return true The claw is closed
     * @return false The claw is not closed
     */
    virtual bool isClosed() = 0;

    /**
     * @brief Checks if the claw is open
     * 
     * @return true The claw is open
     * @return false The claw is not open
     */
    virtual bool isOpen() = 0;
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif