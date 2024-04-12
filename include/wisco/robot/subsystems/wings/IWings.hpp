#ifndef WISCO_ROBOT_SUBSYSTEMS_WINGS_I_WINGS_HPP
#define WISCO_ROBOT_SUBSYSTEMS_WINGS_I_WINGS_HPP

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
 * @brief Namespace for all wings subsystem classes
 * @author Nathan Sandvig
 * 
 */
namespace wings
{

/**
 * @brief Interface for wings subsystems
 * @author Nathan Sandvig
 * 
 */
class IWings
{
public:
    /**
     * @brief Destroy the IWings object
     * 
     */
    virtual ~IWings() = default;

    /**
     * @brief Initializes the wings
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the wings
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Sets the position of the left wing
     * 
     * @param out True for out, false for in
     */
    virtual void setLeftWing(bool out) = 0;

    /**
     * @brief Sets the position of the right wing
     * 
     * @param out True for out, false for in
     */
    virtual void setRightWing(bool out) = 0;

    /**
     * @brief Gets the position of the left wing
     * 
     * @return true The wing is out
     * @return false The wing is in
     */
    virtual bool getLeftWing() = 0;

    /**
     * @brief Gets the position of the right wing
     * 
     * @return true The wing is out
     * @return false The wing is in
     */
    virtual bool getRightWing() = 0;
};
} // namespace wings
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif