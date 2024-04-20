#ifndef WISCO_CONTROL_PATH_I_PATH_FOLLOWER_HPP
#define WISCO_CONTROL_PATH_I_PATH_FOLLOWER_HPP

#include <memory>
#include <vector>

#include "wisco/robot/Robot.hpp"

#include "Point.hpp"
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
 * @brief Namespace for path components
 * @author Nathan Sandvig
 * 
 */
namespace path
{

/**
 * @brief Interface for path following algorithms
 * @author Nathan Sandvig
 * 
 */
class IPathFollower
{
public:
    /**
     * @brief Destroy the IPathFollower object
     * 
     */
    virtual ~IPathFollower() = default;

    /**
     * @brief Initializes the path follower
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the path follower
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Pauses the path follower
     * 
     */
    virtual void pause() = 0;

    /**
     * @brief Resumes the path follower
     * 
     */
    virtual void resume() = 0;

    /**
     * @brief Follows an input path
     * 
     * @param robot The robot being controller
     * @param path The path to follow
     * @param velocity The velocity to move along the path
     */
    virtual void followPath(const std::shared_ptr<robot::Robot>& robot, const std::vector<Point>& path, double velocity) = 0;

    /**
     * @brief Sets the path following velocity
     * 
     * @param velocity The velocity to follow the path
     */
    virtual void setVelocity(double velocity) = 0;

    /**
     * @brief Checks if the target has been reached
     * 
     * @return true The target has been reached
     * @return false The target has not been reached
     */
    virtual bool targetReached() = 0;
};
} // namespace path
} // namespace control
} // namespace wisco

#endif