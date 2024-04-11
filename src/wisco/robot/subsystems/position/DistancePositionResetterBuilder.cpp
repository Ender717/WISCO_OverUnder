#include "wisco/robot/subsystems/position/DistancePositionResetterBuilder.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace position
{
DistancePositionResetterBuilder* DistancePositionResetterBuilder::withDistanceSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor)
{
    m_distance_sensor = std::move(distance_sensor);
    return this;
}

DistancePositionResetterBuilder* DistancePositionResetterBuilder::withLocalX(double local_x)
{
    m_local_x = local_x;
    return this;
}

DistancePositionResetterBuilder* DistancePositionResetterBuilder::withLocalY(double local_y)
{
    m_local_y = local_y;
    return this;
}

DistancePositionResetterBuilder* DistancePositionResetterBuilder::withLocalTheta(double local_theta)
{
    m_local_theta = local_theta;
    return this;
}

std::unique_ptr<IPositionResetter> DistancePositionResetterBuilder::build()
{
    std::unique_ptr<DistancePositionResetter> distance_position_resetter{std::make_unique<DistancePositionResetter>()};
    distance_position_resetter->setDistanceSensor(m_distance_sensor);
    distance_position_resetter->setLocalX(m_local_x);
    distance_position_resetter->setLocalY(m_local_y);
    distance_position_resetter->setLocalTheta(m_local_theta);
    return distance_position_resetter;
}
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco