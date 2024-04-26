#ifndef WISCO_CONTROL_MOTION_I_GO_TO_POINT_HPP
#define WISCO_CONTROL_MOTION_I_GO_TO_POINT_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"

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
 * @brief Namespace for generic motion controls
 * @author Nathan Sandvig
 * 
 */
namespace motion
{

/**
 * @brief Interface for go to point controllers
 * @author Nathan Sandvig
 * 
 */
class IGoToPoint
{
public:
    /**
     * @brief Destroy the IGoToPoint object
     * 
     */
    virtual ~IGoToPoint() = default;

    /**
     * @brief Initializes the go to point controller
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the go to point controller
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Moves to the target position
     * 
     * @param robot The robot
     * @param velocity The motion velocity
     * @param x The target x-coordinate
     * @param y The target y-coordinate
     */
    virtual void goToPoint(const std::shared_ptr<robot::Robot>& robot, double velocity, double x, double y) = 0;

    /**
     * @brief Sets the velocity of the current motion
     * 
     * @param velocity The new velocity
     */
    virtual void setVelocity(double velocity) = 0;

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
} // namespace boomerang
} // namespace control
} // namespace wisco

#endif