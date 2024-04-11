#include "wisco/robot/subsystems/position/DistancePositionResetter.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace position
{
double DistancePositionResetter::bindRadians(double radians)
{
    while (radians > M_PI)
        radians -= (2 * M_PI);
    while (radians < -M_PI)
        radians += (2 * M_PI);
    return radians;
}

void DistancePositionResetter::initialize()
{
    if (m_distance_sensor)
        m_distance_sensor->initialize();
}

void DistancePositionResetter::run()
{
    // No running code
}

double DistancePositionResetter::getResetX(double theta)
{
    double reset_x{};
    if (m_distance_sensor)
    {
        theta = bindRadians(theta);
        double distance{m_distance_sensor->getDistance()};
        double wall_theta{bindRadians(theta + m_local_theta)};
        bool near_wall{std::abs(wall_theta) > M_PI / 2};
        if (near_wall)
            wall_theta = bindRadians(wall_theta + M_PI);
        double sensor_distance{distance * std::cos(wall_theta)};
        double local_x_distance{m_local_x * std::cos(theta)};
        double local_y_distance{m_local_y * std::cos(bindRadians(theta + (M_PI / 2)))};
        double wall_distance{sensor_distance + local_x_distance + local_y_distance};
        if (near_wall)
            reset_x = NEAR_WALL + wall_distance;
        else
            reset_x = FAR_WALL - wall_distance;
    }
    return reset_x;
}

double DistancePositionResetter::getResetY(double theta)
{
    theta -= (M_PI / 2);
    return getResetX(theta);
}

void DistancePositionResetter::setDistanceSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor)
{
    if (distance_sensor)
        m_distance_sensor = std::move(distance_sensor);
}

void DistancePositionResetter::setLocalX(double local_x)
{
    m_local_x = local_x;
}

void DistancePositionResetter::setLocalY(double local_y)
{
    m_local_y = local_y;
}

void DistancePositionResetter::setLocalTheta(double local_theta)
{
    m_local_theta = local_theta;
}
} // namespace position
} // namespace position
} // namespace position
} // namespace position