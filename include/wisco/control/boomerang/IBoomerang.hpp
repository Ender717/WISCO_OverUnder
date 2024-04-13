#ifndef WISCO_CONTROL_BOOMERANG_I_BOOMERANG_HPP
#define WISCO_CONTROL_BOOMERANG_I_BOOMERANG_HPP

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
 * @brief Namespace for boomerang controller components
 * @author Nathan Sandvig
 * 
 */
namespace boomerang
{

/**
 * @brief Interface for boomerang controllers
 * @author Nathan Sandvig
 * 
 */
class IBoomerang
{
public:
    /**
     * @brief Destroy the IBoomerang object
     * 
     */
    virtual ~IBoomerang() = default;

    /**
     * @brief Initializes the boomerang controller
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the boomerang controller
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
     * @param theta The target angle
     */
    virtual void goToPosition(const std::shared_ptr<robot::Robot>& robot, double velocity, double x, double y, double theta) = 0;

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