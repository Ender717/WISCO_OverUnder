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

double DistanceVisionBallDetector::getBallAngle()
{
    double angle{};

    // TODO vision sensor

    return angle;
}

void DistanceVisionBallDetector::setDistanceSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor)
{
    m_distance_sensor = std::move(distance_sensor);
}
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace wisco