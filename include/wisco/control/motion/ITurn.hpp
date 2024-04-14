#ifndef WISCO_CONTROL_MOTION_I_TURN_HPP
#define WISCO_CONTROL_MOTION_I_TURN_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"

#include "ETurnDirection.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for control algorithms
 * @author Nathan Sandvig
 * 
 */
namespace control
{

/**
 * @brief Namespace for basic motion controls
 * @author Nathan Sandvig
 * 
 */
namespace motion
{

/**
 * @brief Interface for turn motion controls
 * @author Nathan Sandvig
 * 
 */
class ITurn
{
public:
    /**
     * @brief Destroy the ITurn object
     * 
     */
    virtual ~ITurn() = default;

    /**
     * @brief Initializes the turn
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the turn
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Turns to the target angle
     * 
     * @param robot The robot
     * @param velocity The angular velocity
     * @param theta The target angle
     * @param direction The turn direction (default AUTO)
     */
    virtual void turnToAngle(const std::shared_ptr<robot::Robot>& robot, double velocity, double theta, ETurnDirection direction = ETurnDirection::AUTO) = 0;

    /**
     * @brief Turns to the target point
     * 
     * @param robot The robot
     * @param velocity The angular velocity
     * @param x The target x-coordinate
     * @param y The target y-coordinate
     * @param direction The turn direction (default AUTO)
     */
    virtual void turnToPoint(const std::shared_ptr<robot::Robot>& robot, double velocity, double x, double y, ETurnDirection direction = ETurnDirection::AUTO) = 0;

    /**
     * @brief Pauses the current motion
     * 
     */
    virtual void pause() = 0;

    /**
     * @brief Resumes the current motion
     * 
     */
    virtual void resume() = 0;

    /**
     * @brief Checks if the target has been reached
     * 
     * @return true The target has been reached
     * @return false The target has not been reached
     */
    virtual bool targetReached() = 0;
};
} // namespace motion
} // namespace control
} // namespace wisco

#endif