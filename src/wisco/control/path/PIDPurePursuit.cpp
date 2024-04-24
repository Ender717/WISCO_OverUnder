#include "wisco/control/path/PIDPurePursuit.hpp"

namespace wisco
{
namespace control
{
namespace path
{
void PIDPurePursuit::taskLoop(void* params)
{
    PIDPurePursuit* instance{static_cast<PIDPurePursuit*>(params)};

    while (true)
    {
        instance->taskUpdate();
    }
}

void PIDPurePursuit::taskUpdate()
{
    if (m_mutex)
        m_mutex->take();
    
    if (!paused && !target_reached)
    {
        auto position{getOdometryPosition()};
        double distance{calculateDistanceToTarget(position)};
        double velocity{std::sqrt(std::pow(position.xV, 2) + std::pow(position.yV, 2))};
        if (found_index == control_path.size() - 1 &&
            distance < m_target_tolerance && 
            velocity < m_target_velocity)
        {
            target_reached = true;
            robot::subsystems::drive::Velocity stop{0, 0};
            setDriveVelocity(stop);
        }
        else
        {
            updateFoundPoints(position);
            Point follow_point{calculateFollowPoint(position)};
            updateVelocity(position, follow_point);
        }
    }

    if (m_mutex)
        m_mutex->give();

    m_delayer->delay(TASK_DELAY);
}

void PIDPurePursuit::setDriveVelocity(robot::subsystems::drive::Velocity velocity)
{
    if (control_robot)
        control_robot->sendCommand(DRIVE_SUBSYSTEM_NAME, DRIVE_SET_VELOCITY_COMMAND_NAME, velocity);
}

double PIDPurePursuit::getDriveRadius()
{
    double radius{};
    if (control_robot)
    {
        double* result{static_cast<double*>(control_robot->getState(DRIVE_SUBSYSTEM_NAME, DRIVE_GET_RADIUS_COMMAND_NAME))};
        if (result)
        {
            radius = *result;
            delete result;
        }
    }
    return radius;
}

robot::subsystems::position::Position PIDPurePursuit::getOdometryPosition()
{
    robot::subsystems::position::Position position{};

    if (control_robot)
    {
        robot::subsystems::position::Position* result{static_cast<robot::subsystems::position::Position*>(control_robot->getState(ODOMETRY_SUBSYSTEM_NAME, ODOMETRY_GET_POSITION_STATE_NAME))};
        if (result)
        {
            position = *result;
            delete result;
        }
    }

    return position;
}

double PIDPurePursuit::calculateDistanceToTarget(wisco::robot::subsystems::position::Position position)
{
    double target_distance{};
    if (!control_path.empty())
        target_distance = distance(position.x, position.y, control_path.back().getX(), control_path.back().getY());
    return target_distance;
}

void PIDPurePursuit::updateFoundPoints(robot::subsystems::position::Position position)
{
    bool loop{true};
    while (loop && found_index < control_path.size() - 1)
    {
        loop = false;
        Point next_point{control_path[found_index + 1]};
        double next_distance{distance(position.x, position.y, next_point.getX(), next_point.getY())};
        if (next_distance <= m_follow_distance)
        {
            ++found_index;
            loop = true;
        }
    }
}

Point PIDPurePursuit::calculateFollowPoint(robot::subsystems::position::Position position)
{   
    Point follow_point{};
    
    if (!control_path.empty())
    {
        if (found_index >= control_path.size() - 1)
        {
            follow_point = control_path.back();
        }
        else
        {
            // Get the relevant position data
            Point p1{control_path[found_index]};
            Point p2{control_path[found_index + 1]};
            double x1{p1.getX() - position.x};
            double y1{p1.getY() - position.y};
            double x2{p2.getX() - position.x};
            double y2{p2.getY() - position.y};

            // Calculate distances
            double dx{x2 - x1};
            double dy{y2 - y1};
            double dr{distance(x1, y1, x2, y2)};
            double D{(x1 * y2) - (x2 * y1)};
            double discriminant{(std::pow(m_follow_distance, 2) * std::pow(dr, 2)) - std::pow(D, 2)};

            // If there are no intersections, return the next target point
            if (discriminant < 0)
            {
                follow_point = p2;
            }
            else
            {
                // Find the intersection points
                double ddy{D * dy};
                double nddx{-1 * D * dx};
                int8_t sdy{sign(dy)};
                double ady{std::abs(dy)};
                double sqrt_discriminant{std::sqrt(discriminant)};
                double dr2{std::pow(dr, 2)};

                double solution1X{(ddy + (sdy * dx * sqrt_discriminant)) / dr2};
                double solution1Y{(nddx + (ady * sqrt_discriminant)) / dr2};
                double solution2X{(ddy - (sdy * dx * sqrt_discriminant)) / dr2};
                double solution2Y{(nddx - (ady * sqrt_discriminant)) / dr2};
                Point solution1{solution1X + position.x, solution1Y + position.y};
                Point solution2{solution2X + position.x, solution2Y + position.y};

                // Pick the point which is further along the line
                double distance1{distance(solution1.getX(), solution1.getY(), p2.getX(), p2.getY())};
                double distance2{distance(solution2.getX(), solution2.getY(), p2.getX(), p2.getY())};
                if (distance1 < distance2)
                    follow_point = solution1;
                else
                    follow_point = solution2;

                // Determine if the point is on the bounded line segment
                double sx{follow_point.getX() - position.x};
                double sy{follow_point.getY() - position.y};
                if (sx < std::min(x1, x2) || sx > std::max(x1, x2) ||
                    sy < std::min(y1, y2) || sy > std::max(y1, y2))
                {
                    follow_point = p1;
                }
            }
        }
    }

    return follow_point;
}

void PIDPurePursuit::updateVelocity(robot::subsystems::position::Position position, path::Point follow_point)
{
    double x_error{follow_point.getX() - position.x};
    double y_error{follow_point.getY() - position.y};
    
    double rotational_error{bindRadians(std::atan2(y_error, x_error) - position.theta)};
    double linear_error{std::cos(rotational_error) * std::sqrt(std::pow(x_error, 2) + std::pow(y_error, 2))};
    if (linear_error < 0)
        rotational_error = bindRadians(rotational_error + M_PI);

    double linear_control{m_linear_pid.getControlValue(0, linear_error)};
    if (std::abs(linear_control) > motion_velocity)
        linear_control *= motion_velocity / std::abs(linear_control);

    double rotational_control{};
    if (std::abs(rotational_error) > M_PI / 4)
        rotational_control = m_rotational_pid.getControlValue(0, rotational_error);
    else
        rotational_control = (2 * getDriveRadius() * std::sin(rotational_error) / m_follow_distance) * linear_control;

    double left_velocity{linear_control - rotational_control};
    double right_velocity{linear_control + rotational_control};
    robot::subsystems::drive::Velocity velocity{left_velocity, right_velocity};
    setDriveVelocity(velocity);
}

void PIDPurePursuit::initialize()
{
    m_linear_pid.reset();
    m_rotational_pid.reset();
}

void PIDPurePursuit::run()
{
    if (m_task)
        m_task->start(&PIDPurePursuit::taskLoop, this);
}

void PIDPurePursuit::followPath(const std::shared_ptr<robot::Robot>& robot, const std::vector<Point>& path, double velocity)
{
    if (m_mutex)
        m_mutex->take();

    control_robot = robot;
    control_path = path;
    found_index = 0;
    motion_velocity = velocity;
    target_reached = false;

    if (m_mutex)
        m_mutex->give();
}

void PIDPurePursuit::setVelocity(double velocity)
{
    if (m_mutex)
        m_mutex->take();
    
    motion_velocity = velocity;

    if (m_mutex)
        m_mutex->give();
}

void PIDPurePursuit::pause()
{
    if (m_mutex)
        m_mutex->take();
    
    paused = true;
    robot::subsystems::drive::Velocity stop{0, 0};
    setDriveVelocity(stop);

    if (m_mutex)
        m_mutex->give();
}

void PIDPurePursuit::resume()
{
    if (m_mutex)
        m_mutex->take();

    paused = false;

    if (m_mutex)
        m_mutex->give();
}

bool PIDPurePursuit::targetReached()
{
    return target_reached;
}

void PIDPurePursuit::setDelayer(const std::unique_ptr<rtos::IDelayer>& delayer)
{
    m_delayer = delayer->clone();
}

void PIDPurePursuit::setMutex(std::unique_ptr<rtos::IMutex>& mutex)
{
    m_mutex = std::move(mutex);
}

void PIDPurePursuit::setTask(std::unique_ptr<rtos::ITask>& task)
{
    m_task = std::move(task);
}

void PIDPurePursuit::setLinearPID(PID linear_pid)
{
    m_linear_pid = linear_pid;
}

void PIDPurePursuit::setRotationalPID(PID rotational_pid)
{
    m_rotational_pid = rotational_pid;
}

void PIDPurePursuit::setFollowDistance(double follow_distance)
{
    m_follow_distance = follow_distance;
}

void PIDPurePursuit::setTargetTolerance(double target_tolerance)
{
    m_target_tolerance = target_tolerance;
}

void PIDPurePursuit::setTargetVelocity(double target_velocity)
{
    m_target_velocity = target_velocity;
}
} // namespace path
} // namespace control
} // namespace wisco