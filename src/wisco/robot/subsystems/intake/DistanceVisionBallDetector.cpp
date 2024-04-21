#include "wisco/robot/subsystems/intake/DistanceVisionBallDetector.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace intake
{
void DistanceVisionBallDetector::initialize()
{
    if (m_distance_sensor)
        m_distance_sensor->initialize();
    if (m_vision_sensor)
        m_vision_sensor->initialize();
}

void DistanceVisionBallDetector::run()
{
    // No running code
}

double DistanceVisionBallDetector::getBallDistance()
{
    double distance{};
    if (m_distance_sensor)
        distance = m_distance_sensor->getDistance();
    return distance;
}

std::vector<io::VisionObject> DistanceVisionBallDetector::getBallVisionObjects()
{
    std::vector<io::VisionObject> vision_objects{};

    if (m_vision_sensor)
        vision_objects = m_vision_sensor->getObjects();

    return vision_objects;
}

void DistanceVisionBallDetector::setDistanceSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor)
{
    if (distance_sensor)
        m_distance_sensor = std::move(distance_sensor);
}

void DistanceVisionBallDetector::setVisionSensor(std::unique_ptr<io::IVisionSensor>& vision_sensor)
{
    if (vision_sensor)
        m_vision_sensor = std::move(vision_sensor);
}

} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco