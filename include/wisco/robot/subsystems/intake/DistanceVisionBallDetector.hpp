#ifndef WISCO_ROBOT_SUBSYSTEMS_INTAKE_DISTANCE_VISION_BALL_DETECTOR_HPP
#define WISCO_ROBOT_SUBSYSTEMS_INTAKE_DISTANCE_VISION_BALL_DETECTOR_HPP

#include <memory>

#include "wisco/io/IDistanceSensor.hpp"
// TODO vision sensor

#include "IBallDetector.hpp"

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
 * @brief Ball detection system that uses a distance and vision sensor
 * @author Nathan Sandvig
 * 
 */
class DistanceVisionBallDetector : public IBallDetector
{
private:
    /**
     * @brief The distance sensor
     * 
     */
    std::unique_ptr<io::IDistanceSensor> m_distance_sensor{};

    // TODO vision sensor

public:
    /**
     * @brief Initializes the ball detector
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the ball detector
     * 
     */
    void run() override;

    /**
     * @brief Get the distance to the ball
     * 
     * @return double The distance to the ball
     */
    double getBallDistance() override;

    /**
     * @brief Get the angle to the ball
     * 
     * @return double The angle to the ball
     */
    double getBallAngle() override;

    /**
     * @brief Sets the distance sensor
     * 
     * @param distance_sensor The distance sensor
     */
    void setDistanceSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor);
};
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif