#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_I_POSITION_RESETTER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_I_POSITION_RESETTER_HPP

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
 * @brief Namespace for all position subsystem classes
 * @author Nathan Sandvig
 * 
 */
namespace position
{
    
/**
 * @brief Interface for position resetting subsystems
 * @author Nathan Sandvig
 * 
 */
class IPositionResetter
{
public:
    /**
     * @brief Destroy the IPositionResetter object
     * 
     */
    virtual ~IPositionResetter() = default;

    /**
     * @brief Initializes the position resetting system
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the position tracking system
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Get the reset position for X
     * 
     * @param theta The current robot angle
     * @return double The X reset position
     */
    virtual double getResetX(double theta) = 0;

    /**
     * @brief Get the reset position for Y
     * 
     * @param theta The current robot angle
     * @return double The Y reset position
     */
    virtual double getResetY(double theta) = 0;
};
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif
