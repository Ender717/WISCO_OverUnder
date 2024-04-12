#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_I_WINCH_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_I_WINCH_HPP

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
 * @brief Interface for winches with an engaged and disengaged position
 * @author Nathan Sandvig
 * 
 */
class IWinch
{
public:
    /**
     * @brief Destroy the IWinch object
     * 
     */
    virtual ~IWinch() = default;

    /**
     * @brief Initializes the winch
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the winch
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Engages the winch
     * 
     */
    virtual void engage() = 0;

    /**
     * @brief Disengages the winch
     * 
     */
    virtual void disengage() = 0;

    /**
     * @brief Checks if the winch is engaged
     * 
     * @return true The winch is engaged
     * @return false The winch is not engaged
     */
    virtual bool isEngaged() = 0;

    /**
     * @brief Checks if the winch is disengaged
     * 
     * @return true The winch is disengaged
     * @return false The winch is not disengaged
     */
    virtual bool isDisengaged() = 0;
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif