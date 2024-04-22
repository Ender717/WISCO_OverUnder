#ifndef WISCO_CONTROL_MOTION_I_DRIVE_STRAIGHT_HPP
#define WISCO_CONTROL_MOTION_I_DRIVE_STRAIGHT_HPP

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
 * @brief Namespace for basic motion controls
 * @author Nathan Sandvig
 * 
 */
namespace motion
{

/**
 * @brief Interface for drive straight motion controls
 * @author Nathan Sandvig
 * 
 */
class IDriveStraight
{
public:
    /**
     * @brief Destroy the IDriveStraight object
     * 
     */
    virtual ~IDriveStraight() = default;

    /**
     * @brief Initializes the drive straight
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the drive straight
     * 
     */
    virtual void run() = 0;

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
     * @brief Drives straight for a set distance
     * 
     * @param robot The robot
     * @param distance The distance to drive (negative for backwards motion)
     * @param velocity The velocity for the motion
     * @param theta The angle for the motion
     */
    virtual void driveStraight(std::shared_ptr<robot::Robot> robot,
                               double distance, double velocity, double theta) = 0;

    /**
     * @brief Sets the velocity of the motion
     * 
     * @param velocity The velocity of the motion
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
} // namespace motion
} // namespace control
} // namespace wisco

#endif