#ifndef WISCO_ROBOT_SUBSYSTEMS_INTAKE_DISTANCE_VISION_BALL_DETECTOR_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_INTAKE_DISTANCE_VISION_BALL_DETECTOR_BUILDER_HPP

#include "DistanceVisionBallDetector.hpp"

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
class DistanceVisionBallDetectorBuilder
{
private:
    /**
     * @brief The distance sensor
     * 
     */
    std::unique_ptr<io::IDistanceSensor> m_distance_sensor{};

    /**
     * @brief The vision sensor
     * 
     */
    std::unique_ptr<io::IVisionSensor> m_vision_sensor{};

public:
    /**
     * @brief Adds a distance sensor to the build
     * 
     * @param distance_sensor The distance sensor
     * @return DistanceVisionBallDetectorBuilder* This object for build chaining
     */
    DistanceVisionBallDetectorBuilder* withDistanceSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor);

    /**
     * @brief Adds a vision sensor to the build
     * 
     * @param vision_sensor The vision sensor
     * @return DistanceVisionBallDetectorBuilder* This object for build chaining
     */
    DistanceVisionBallDetectorBuilder* withVisionSensor(std::unique_ptr<io::IVisionSensor>& vision_sensor);

    /**
     * @brief Builds the distance vision ball detector
     * 
     * @return std::unique_ptr<IBallDetector> The distance vision ball detector as an IBallDetector interface object
     */
    std::unique_ptr<IBallDetector> build();
};
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif