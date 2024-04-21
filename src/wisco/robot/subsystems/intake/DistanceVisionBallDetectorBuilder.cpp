#include "wisco/robot/subsystems/intake/DistanceVisionBallDetectorBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace intake
{
DistanceVisionBallDetectorBuilder* DistanceVisionBallDetectorBuilder::withDistanceSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor)
{
    m_distance_sensor = std::move(distance_sensor);
    return this;
}

DistanceVisionBallDetectorBuilder* DistanceVisionBallDetectorBuilder::withVisionSensor(std::unique_ptr<io::IVisionSensor>& vision_sensor)
{
    m_vision_sensor = std::move(vision_sensor);
    return this;
}

std::unique_ptr<IBallDetector> DistanceVisionBallDetectorBuilder::build()
{
    std::unique_ptr<DistanceVisionBallDetector> distance_vision_ball_detector{std::make_unique<DistanceVisionBallDetector>()};
    distance_vision_ball_detector->setDistanceSensor(m_distance_sensor);
    distance_vision_ball_detector->setVisionSensor(m_vision_sensor);
    return distance_vision_ball_detector;
}
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco