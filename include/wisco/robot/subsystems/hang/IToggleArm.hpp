#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_I_TOGGLE_ARM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_I_TOGGLE_ARM_HPP

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
 * @brief Interface for arms with an up and down position
 * @author Nathan Sandvig
 * 
 */
class IToggleArm
{
public:
        /**
     * @brief Destroy the IToggleArm object
     * 
     */
    virtual ~IToggleArm() = default;

    /**
     * @brief Initializes the arm
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the arm
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Sets the arm to the down position
     * 
     */
    virtual void setDown() = 0;

    /**
     * @brief Sets the arm to the up position
     * 
     */
    virtual void setUp() = 0;

    /**
     * @brief Checks if the arm is in the down position
     * 
     * @return true The arm is in the down position
     * @return false The arm is not in the down position
     */
    virtual bool isDown() = 0;

    /**
     * @brief Checks if the arm is in the up position
     * 
     * @return true The arm is in the up position
     * @return false The arm is not in the up position
     */
    virtual bool isUp() = 0;
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif