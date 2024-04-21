#ifndef WISCO_ROBOT_SUBSYSTEMS_INTAKE_I_BALL_DETECTOR_HPP
#define WISCO_ROBOT_SUBSYSTEMS_INTAKE_I_BALL_DETECTOR_HPP

#include <vector>

#include "wisco/io/VisionObject.hpp"

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
 * @brief Namespace for intake classes
 * @author Nathan Sandvig
 * 
 */
namespace intake
{

/**
 * @brief Interface for ball detection system
 * @author Nathan Sandvig
 * 
 */
class IBallDetector
{
public:
    /**
     * @brief Destroy the IBallDetector object
     * 
     */
    virtual ~IBallDetector() = default;

    /**
     * @brief Initializes the ball detector
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the ball detector
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Get the distance to the ball
     * 
     * @return double The distance to the ball
     */
    virtual double getBallDistance() = 0;

    /**
     * @brief Get the ball vision objects
     * 
     * @return std::vector<io::VisionObject> The ball vision objects
     */
    virtual std::vector<io::VisionObject> getBallVisionObjects() = 0;
};
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif