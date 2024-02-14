#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_I_POSITION_TRACKER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_I_POSITION_TRACKER_HPP

#include "Position.hpp"

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
 * @brief Interface for position tracking subsystems
 * @author Nathan Sandvig
 * 
 */
class IPositionTracker
{
public:
    /**
     * @brief Destroy the IPositionTracker object
     * 
     */
    virtual ~IPositionTracker() = default;

    /**
     * @brief Initializes the position tracking system
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the position tracking system
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Set the position of the position tracking system
     * 
     * @param position The new position
     */
    virtual void setPosition(Position position) = 0;

    /**
     * @brief Get the position of the system
     * 
     * @return Position The position of the system
     */
    virtual Position getPosition() = 0;
};
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif