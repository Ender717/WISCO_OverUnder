#include "wisco/configs/BlueConfiguration.hpp"
#include "wisco/sensors/IDistanceTrackingSensor.hpp"

namespace wisco
{
namespace configs
{
std::string BlueConfiguration::getName()
{
    return CONFIGURATION_NAME;
}

std::shared_ptr<robot::Robot> BlueConfiguration::buildRobot()
{
    std::shared_ptr<robot::Robot> robot{std::make_unique<robot::Robot>()};

    // Odometry creation
    robot::subsystems::position::InertialOdometryBuilder inertial_odometry_builder{};
    std::unique_ptr<wisco::rtos::IClock> pros_clock{std::make_unique<pros_adapters::ProsClock>()};
    std::unique_ptr<wisco::rtos::IDelayer> pros_delayer{std::make_unique<pros_adapters::ProsDelayer>()};
    std::unique_ptr<wisco::rtos::IMutex> pros_mutex{std::make_unique<pros_adapters::ProsMutex>()};
    std::unique_ptr<wisco::rtos::ITask> pros_task{std::make_unique<pros_adapters::ProsTask>()};
    std::unique_ptr<pros::Imu> pros_heading{std::make_unique<pros::Imu>(ODOMETRY_HEADING_PORT)};
    std::unique_ptr<wisco::sensors::IHeadingSensor> pros_heading_sensor{std::make_unique<pros_adapters::ProsHeading>(pros_heading)};
    std::unique_ptr<pros::Rotation> pros_linear_rotation{std::make_unique<pros::Rotation>(ODOMETRY_LINEAR_PORT)};
    std::unique_ptr<wisco::sensors::IRotationSensor> pros_linear_rotation_sensor{std::make_unique<pros_adapters::ProsRotation>(pros_linear_rotation)};
    std::unique_ptr<wisco::sensors::IDistanceTrackingSensor> linear_tracking_wheel{std::make_unique<wisco::hal::TrackingWheel>(pros_linear_rotation_sensor, ODOMETRY_LINEAR_RADIUS)};
    std::unique_ptr<pros::Rotation> pros_strafe_rotation{std::make_unique<pros::Rotation>(ODOMETRY_STRAFE_PORT)};
    std::unique_ptr<wisco::sensors::IRotationSensor> pros_strafe_rotation_sensor{std::make_unique<pros_adapters::ProsRotation>(pros_strafe_rotation)};
    std::unique_ptr<wisco::sensors::IDistanceTrackingSensor> strafe_tracking_wheel{std::make_unique<wisco::hal::TrackingWheel>(pros_strafe_rotation_sensor, ODOMETRY_STRAFE_RADIUS)};
    std::unique_ptr<wisco::robot::subsystems::position::IPositionTracker> inertial_odometry
    {
        inertial_odometry_builder.
        withClock(pros_clock)->
        withDelayer(pros_delayer)->
        withMutex(pros_mutex)->
        withTask(pros_task)->
        withHeadingSensor(pros_heading_sensor)->
        withLinearDistanceTrackingSensor(linear_tracking_wheel)->
        withLinearDistanceTrackingOffset(ODOMETRY_LINEAR_OFFSET)->
        withStrafeDistanceTrackingSensor(strafe_tracking_wheel)->
        withStrafeDistanceTrackingOffset(ODOMETRY_STRAFE_OFFSET)->
        build()
    };
    std::unique_ptr<wisco::robot::ASubsystem> odometry_subsystem{std::make_unique<wisco::robot::subsystems::position::PositionSubsystem>(inertial_odometry)};
    robot->addSubsystem(odometry_subsystem);
    return robot;
}
}
}