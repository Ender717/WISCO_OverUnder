#include "wisco/configs/BlueConfiguration.hpp"

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
    std::unique_ptr<wisco::rtos::IClock> odometry_pros_clock{std::make_unique<pros_adapters::ProsClock>()};
    std::unique_ptr<wisco::rtos::IDelayer> odometry_pros_delayer{std::make_unique<pros_adapters::ProsDelayer>()};
    std::unique_ptr<wisco::rtos::IMutex> odometry_pros_mutex{std::make_unique<pros_adapters::ProsMutex>()};
    std::unique_ptr<wisco::rtos::ITask> odometry_pros_task{std::make_unique<pros_adapters::ProsTask>()};
    std::unique_ptr<pros::Imu> odometry_pros_heading{std::make_unique<pros::Imu>(ODOMETRY_HEADING_PORT)};
    std::unique_ptr<wisco::io::IHeadingSensor> odometry_pros_heading_sensor{std::make_unique<pros_adapters::ProsHeading>(odometry_pros_heading, ODOMETRY_HEADING_TUNING_CONSTANT)};
    std::unique_ptr<pros::Rotation> odometry_pros_linear_rotation{std::make_unique<pros::Rotation>(ODOMETRY_LINEAR_PORT)};
    std::unique_ptr<wisco::io::IRotationSensor> odometry_pros_linear_rotation_sensor{std::make_unique<pros_adapters::ProsRotation>(odometry_pros_linear_rotation)};
    std::unique_ptr<wisco::io::IDistanceTrackingSensor> odometry_linear_tracking_wheel{std::make_unique<wisco::hal::TrackingWheel>(odometry_pros_linear_rotation_sensor, ODOMETRY_LINEAR_RADIUS)};
    std::unique_ptr<pros::Rotation> odometry_pros_strafe_rotation{std::make_unique<pros::Rotation>(ODOMETRY_STRAFE_PORT)};
    std::unique_ptr<wisco::io::IRotationSensor> odometry_pros_strafe_rotation_sensor{std::make_unique<pros_adapters::ProsRotation>(odometry_pros_strafe_rotation)};
    std::unique_ptr<wisco::io::IDistanceTrackingSensor> odometry_strafe_tracking_wheel{std::make_unique<wisco::hal::TrackingWheel>(odometry_pros_strafe_rotation_sensor, ODOMETRY_STRAFE_RADIUS)};
    std::unique_ptr<wisco::robot::subsystems::position::IPositionTracker> inertial_odometry
    {
        inertial_odometry_builder.
        withClock(odometry_pros_clock)->
        withDelayer(odometry_pros_delayer)->
        withMutex(odometry_pros_mutex)->
        withTask(odometry_pros_task)->
        withHeadingSensor(odometry_pros_heading_sensor)->
        withLinearDistanceTrackingSensor(odometry_linear_tracking_wheel)->
        withLinearDistanceTrackingOffset(ODOMETRY_LINEAR_OFFSET)->
        withStrafeDistanceTrackingSensor(odometry_strafe_tracking_wheel)->
        withStrafeDistanceTrackingOffset(ODOMETRY_STRAFE_OFFSET)->
        build()
    };
    std::unique_ptr<wisco::robot::ASubsystem> odometry_subsystem{std::make_unique<wisco::robot::subsystems::position::PositionSubsystem>(inertial_odometry)};
    robot->addSubsystem(odometry_subsystem);

    // Drive creation
    wisco::robot::subsystems::drive::KinematicDifferentialDriveBuilder kinematic_differential_drive_builder{};
    std::unique_ptr<wisco::rtos::IDelayer> drive_pros_delayer{std::make_unique<pros_adapters::ProsDelayer>()};
    std::unique_ptr<wisco::rtos::IMutex> drive_pros_mutex{std::make_unique<pros_adapters::ProsMutex>()};
    std::unique_ptr<wisco::rtos::ITask> drive_pros_task{std::make_unique<pros_adapters::ProsTask>()};
    std::unique_ptr<wisco::rtos::IClock> drive_left_velocity_profile_pros_clock{std::make_unique<pros_adapters::ProsClock>()};
    std::unique_ptr<wisco::robot::subsystems::drive::IVelocityProfile> drive_left_velocity_profile{std::make_unique<wisco::robot::subsystems::drive::CurveVelocityProfile>(drive_left_velocity_profile_pros_clock, DRIVE_VELOCITY_PROFILE_JERK_RATE, DRIVE_VELOCITY_PROFILE_MAX_ACCELERATION)};
    std::unique_ptr<wisco::rtos::IClock> drive_right_velocity_profile_pros_clock{std::make_unique<pros_adapters::ProsClock>()};
    std::unique_ptr<wisco::robot::subsystems::drive::IVelocityProfile> drive_right_velocity_profile{std::make_unique<wisco::robot::subsystems::drive::CurveVelocityProfile>(drive_right_velocity_profile_pros_clock, DRIVE_VELOCITY_PROFILE_JERK_RATE, DRIVE_VELOCITY_PROFILE_MAX_ACCELERATION)};
    std::unique_ptr<pros::Motor> drive_pros_left_motor_1{std::make_unique<pros::Motor>(DRIVE_LEFT_MOTOR_1_PORT, DRIVE_LEFT_MOTOR_1_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> drive_pros_left_motor_1_motor{std::make_unique<pros_adapters::ProsV5Motor>(drive_pros_left_motor_1)};
    std::unique_ptr<pros::Motor> drive_pros_left_motor_2{std::make_unique<pros::Motor>(DRIVE_LEFT_MOTOR_2_PORT, DRIVE_LEFT_MOTOR_2_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> drive_pros_left_motor_2_motor{std::make_unique<pros_adapters::ProsV5Motor>(drive_pros_left_motor_2)};
    std::unique_ptr<pros::Motor> drive_pros_left_motor_3{std::make_unique<pros::Motor>(DRIVE_LEFT_MOTOR_3_PORT, DRIVE_LEFT_MOTOR_3_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> drive_pros_left_motor_3_motor{std::make_unique<pros_adapters::ProsV5Motor>(drive_pros_left_motor_3)};
    std::unique_ptr<pros::Motor> drive_pros_left_motor_4{std::make_unique<pros::Motor>(DRIVE_LEFT_MOTOR_4_PORT, DRIVE_LEFT_MOTOR_4_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> drive_pros_left_motor_4_motor{std::make_unique<pros_adapters::ProsV5Motor>(drive_pros_left_motor_4)};
    std::unique_ptr<pros::Motor> drive_pros_right_motor_1{std::make_unique<pros::Motor>(DRIVE_RIGHT_MOTOR_1_PORT, DRIVE_RIGHT_MOTOR_1_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> drive_pros_right_motor_1_motor{std::make_unique<pros_adapters::ProsV5Motor>(drive_pros_right_motor_1)};
    std::unique_ptr<pros::Motor> drive_pros_right_motor_2{std::make_unique<pros::Motor>(DRIVE_RIGHT_MOTOR_2_PORT, DRIVE_RIGHT_MOTOR_2_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> drive_pros_right_motor_2_motor{std::make_unique<pros_adapters::ProsV5Motor>(drive_pros_right_motor_2)};
    std::unique_ptr<pros::Motor> drive_pros_right_motor_3{std::make_unique<pros::Motor>(DRIVE_RIGHT_MOTOR_3_PORT, DRIVE_RIGHT_MOTOR_3_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> drive_pros_right_motor_3_motor{std::make_unique<pros_adapters::ProsV5Motor>(drive_pros_right_motor_3)};
    std::unique_ptr<pros::Motor> drive_pros_right_motor_4{std::make_unique<pros::Motor>(DRIVE_RIGHT_MOTOR_4_PORT, DRIVE_RIGHT_MOTOR_4_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> drive_pros_right_motor_4_motor{std::make_unique<pros_adapters::ProsV5Motor>(drive_pros_right_motor_4)};
    std::unique_ptr<wisco::robot::subsystems::drive::IDifferentialDrive> differential_drive
    {
        kinematic_differential_drive_builder.
        withDelayer(drive_pros_delayer)->
        withMutex(drive_pros_mutex)->
        withTask(drive_pros_task)->
        withLeftVelocityProfile(drive_left_velocity_profile)->
        withRightVelocityProfile(drive_right_velocity_profile)->
        withLeftMotor(drive_pros_left_motor_1_motor)->
        withLeftMotor(drive_pros_left_motor_2_motor)->
        withLeftMotor(drive_pros_left_motor_3_motor)->
        withLeftMotor(drive_pros_left_motor_4_motor)->
        withRightMotor(drive_pros_right_motor_1_motor)->
        withRightMotor(drive_pros_right_motor_2_motor)->
        withRightMotor(drive_pros_right_motor_3_motor)->
        withRightMotor(drive_pros_right_motor_4_motor)->
        withMass(DRIVE_MASS)->
        withRadius(DRIVE_RADIUS)->
        withMomentOfInertia(DRIVE_MOMENT_OF_INERTIA)->
        withGearRatio(DRIVE_GEAR_RATIO)->
        withWheelRadius(DRIVE_WHEEL_RADIUS)->
        build()
    };
    std::unique_ptr<wisco::robot::ASubsystem> drive_subsystem{std::make_unique<wisco::robot::subsystems::drive::DifferentialDriveSubsystem>(differential_drive)};
    robot->addSubsystem(drive_subsystem);
    
    return robot;
}
}
}