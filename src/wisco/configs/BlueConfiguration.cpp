#include "wisco/configs/BlueConfiguration.hpp"

namespace wisco
{
namespace configs
{
std::string BlueConfiguration::getName()
{
    return CONFIGURATION_NAME;
}

std::shared_ptr<control::ControlSystem> BlueConfiguration::buildControlSystem()
{
    std::shared_ptr<control::ControlSystem> control_system{std::make_shared<control::ControlSystem>()};

    std::unique_ptr<rtos::IClock> pros_clock{std::make_unique<pros_adapters::ProsClock>()};
    std::unique_ptr<rtos::IDelayer> pros_delayer{std::make_unique<pros_adapters::ProsDelayer>()};

    wisco::control::boomerang::PIDBoomerangBuilder pid_boomerang_builder{};
    std::unique_ptr<rtos::IMutex> boomerang_pros_mutex{std::make_unique<pros_adapters::ProsMutex>()};
    std::unique_ptr<rtos::ITask> boomerang_pros_task{std::make_unique<pros_adapters::ProsTask>()};
    wisco::control::PID boomerang_linear_pid{pros_clock, BOOMERANG_LINEAR_KP, BOOMERANG_LINEAR_KI, BOOMERANG_LINEAR_KD};
    wisco::control::PID boomerang_rotational_pid{pros_clock, BOOMERANG_ROTATIONAL_KP, BOOMERANG_ROTATIONAL_KI, BOOMERANG_ROTATIONAL_KD};
    std::unique_ptr<wisco::control::boomerang::IBoomerang> pid_boomerang
    {
        pid_boomerang_builder.
        withDelayer(pros_delayer)->
        withMutex(boomerang_pros_mutex)->
        withTask(boomerang_pros_task)->
        withLinearPID(boomerang_linear_pid)->
        withRotationalPID(boomerang_rotational_pid)->
        withLead(BOOMERANG_LEAD)->
        withTargetTolerance(BOOMERANG_TARGET_TOLERANCE)->
        withTargetVelocity(BOOMERANG_TARGET_VELOCITY)->
        build()
    };
    std::unique_ptr<wisco::control::AControl> boomerang_control{std::make_unique<wisco::control::boomerang::BoomerangControl>(pid_boomerang)};
    control_system->addControl(boomerang_control);

    wisco::control::motion::PIDTurnBuilder pid_turn_builder{};
    std::unique_ptr<rtos::IMutex> turn_pros_mutex{std::make_unique<pros_adapters::ProsMutex>()};
    std::unique_ptr<rtos::ITask> turn_pros_task{std::make_unique<pros_adapters::ProsTask>()};
    wisco::control::PID turn_pid{pros_clock, TURN_KP, TURN_KI, TURN_KD};
    std::unique_ptr<wisco::control::motion::ITurn> pid_turn
    {
        pid_turn_builder.
        withDelayer(pros_delayer)->
        withMutex(turn_pros_mutex)->
        withTask(turn_pros_task)->
        withPID(turn_pid)->
        withTargetTolerance(TURN_TARGET_TOLERANCE)->
        withTargetVelocity(TURN_TARGET_VELOCITY)->
        build()
    };
    std::unique_ptr<wisco::control::AControl> motion_control{std::make_unique<wisco::control::motion::MotionControl>(pid_turn)};
    control_system->addControl(motion_control);

    wisco::control::path::PIDPurePursuitBuilder pid_pure_pursuit_builder{};
    std::unique_ptr<rtos::IMutex> pure_pursuit_pros_mutex{std::make_unique<pros_adapters::ProsMutex>()};
    std::unique_ptr<rtos::ITask> pure_pursuit_pros_task{std::make_unique<pros_adapters::ProsTask>()};
    wisco::control::PID pure_pursuit_linear_pid{pros_clock, PURE_PURSUIT_LINEAR_KP, PURE_PURSUIT_LINEAR_KI, PURE_PURSUIT_LINEAR_KD};
    wisco::control::PID pure_pursuit_rotational_pid{pros_clock, PURE_PURSUIT_ROTATIONAL_KP, PURE_PURSUIT_ROTATIONAL_KI, PURE_PURSUIT_ROTATIONAL_KD};
    std::unique_ptr<wisco::control::path::IPathFollower> pid_pure_pursuit
    {
        pid_pure_pursuit_builder.
        withDelayer(pros_delayer)->
        withMutex(pure_pursuit_pros_mutex)->
        withTask(pure_pursuit_pros_task)->
        withLinearPID(pure_pursuit_linear_pid)->
        withRotationalPID(pure_pursuit_rotational_pid)->
        withFollowDistance(PURE_PURSUIT_FOLLOW_DISTANCE)->
        withTargetTolerance(PURE_PURSUIT_TARGET_TOLERANCE)->
        withTargetVelocity(PURE_PURSUIT_TARGET_VELOCITY)->
        build()
    };
    std::unique_ptr<wisco::control::AControl> pure_pursuit_control{std::make_unique<wisco::control::path::PathFollowingControl>(pid_pure_pursuit)};
    control_system->addControl(pure_pursuit_control);

    return control_system;
}

std::shared_ptr<user::IController> BlueConfiguration::buildController()
{
    std::unique_ptr<pros::Controller> pros_controller{std::make_unique<pros::Controller>(pros::E_CONTROLLER_MASTER)};
    std::shared_ptr<user::IController> pros_controller_controller{std::make_shared<pros_adapters::ProsController>(pros_controller)};
    return pros_controller_controller;
}

std::shared_ptr<robot::Robot> BlueConfiguration::buildRobot()
{
    std::shared_ptr<robot::Robot> robot{std::make_shared<robot::Robot>()};

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
    robot::subsystems::position::DistancePositionResetterBuilder distance_position_resetter_builder{};
    if (RESETTER_DISTANCE_PORT)
    {
        std::unique_ptr<pros::Distance> resetter_pros_distance{std::make_unique<pros::Distance>(RESETTER_DISTANCE_PORT)};
        std::unique_ptr<wisco::io::IDistanceSensor> resetter_pros_distance_sensor{std::make_unique<pros_adapters::ProsDistance>(resetter_pros_distance, RESETTER_DISTANCE_CONSTANT, RESETTER_DISTANCE_OFFSET)};
        distance_position_resetter_builder.withDistanceSensor(resetter_pros_distance_sensor);
    }
    std::unique_ptr<wisco::robot::subsystems::position::IPositionResetter> distance_position_resetter
    {
        distance_position_resetter_builder.
        withLocalX(RESETTER_OFFSET_X)->
        withLocalY(RESETTER_OFFSET_Y)->
        withLocalTheta(RESETTER_OFFSET_THETA)->
        build()
    };
    std::unique_ptr<wisco::robot::ASubsystem> odometry_subsystem{std::make_unique<wisco::robot::subsystems::position::PositionSubsystem>(inertial_odometry, distance_position_resetter)};
    robot->addSubsystem(odometry_subsystem);

    // Drive creation
    if (DRIVE_KINEMATIC)
    {
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
    }
    else
    {
        wisco::robot::subsystems::drive::DirectDifferentialDriveBuilder direct_differential_drive_builder{};
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
            direct_differential_drive_builder.
            withLeftMotor(drive_pros_left_motor_1_motor)->
            withLeftMotor(drive_pros_left_motor_2_motor)->
            withLeftMotor(drive_pros_left_motor_3_motor)->
            withLeftMotor(drive_pros_left_motor_4_motor)->
            withRightMotor(drive_pros_right_motor_1_motor)->
            withRightMotor(drive_pros_right_motor_2_motor)->
            withRightMotor(drive_pros_right_motor_3_motor)->
            withRightMotor(drive_pros_right_motor_4_motor)->
            withVelocityToVoltage(DRIVE_VELOCITY_TO_VOLTAGE)->
            withGearRatio(DRIVE_GEAR_RATIO)->
            withWheelRadius(DRIVE_WHEEL_RADIUS)->
            withRadius(DRIVE_RADIUS)->
            build()
        };
        std::unique_ptr<wisco::robot::ASubsystem> drive_subsystem{std::make_unique<wisco::robot::subsystems::drive::DifferentialDriveSubsystem>(differential_drive)};
        robot->addSubsystem(drive_subsystem);
    }

    // Intake creation
    wisco::robot::subsystems::intake::PIDIntakeBuilder pid_intake_builder{};
    std::unique_ptr<wisco::rtos::IClock> intake_pros_clock{std::make_unique<pros_adapters::ProsClock>()};
    std::unique_ptr<wisco::rtos::IDelayer> intake_pros_delayer{std::make_unique<pros_adapters::ProsDelayer>()};
    std::unique_ptr<wisco::rtos::IMutex> intake_pros_mutex{std::make_unique<pros_adapters::ProsMutex>()};
    std::unique_ptr<wisco::rtos::ITask> intake_pros_task{std::make_unique<pros_adapters::ProsTask>()};
    wisco::control::PID intake_pid{intake_pros_clock, INTAKE_KP, INTAKE_KI, INTAKE_KD};
    std::unique_ptr<pros::Motor> intake_pros_motor_1{std::make_unique<pros::Motor>(INTAKE_MOTOR_1_PORT, INTAKE_MOTOR_1_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> intake_pros_motor_1_motor{std::make_unique<pros_adapters::ProsV5Motor>(intake_pros_motor_1)};
    std::unique_ptr<pros::Motor> intake_pros_motor_2{std::make_unique<pros::Motor>(INTAKE_MOTOR_2_PORT, INTAKE_MOTOR_2_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> intake_pros_motor_2_motor{std::make_unique<pros_adapters::ProsV5Motor>(intake_pros_motor_2)};
    std::unique_ptr<wisco::robot::subsystems::intake::IIntake> pid_intake
    {
        pid_intake_builder.
        withClock(intake_pros_clock)->
        withDelayer(intake_pros_delayer)->
        withMutex(intake_pros_mutex)->
        withTask(intake_pros_task)->
        withPID(intake_pid)->
        withMotor(intake_pros_motor_1_motor)->
        withMotor(intake_pros_motor_2_motor)->
        withRollerRadius(INTAKE_ROLLER_RADIUS)->
        build()
    };
    wisco::robot::subsystems::intake::DistanceVisionBallDetectorBuilder distance_vision_ball_detector_builder{};
    if (BALL_DETECTOR_DISTANCE_PORT)
    {
        std::unique_ptr<pros::Distance> ball_detector_pros_distance{std::make_unique<pros::Distance>(BALL_DETECTOR_DISTANCE_PORT)};
        std::unique_ptr<wisco::io::IDistanceSensor> ball_detector_pros_distance_sensor{std::make_unique<pros_adapters::ProsDistance>(ball_detector_pros_distance, BALL_DETECTOR_DISTANCE_CONSTANT, BALL_DETECTOR_DISTANCE_OFFSET)};
        distance_vision_ball_detector_builder.withDistanceSensor(ball_detector_pros_distance_sensor);
    }
    std::unique_ptr<wisco::robot::subsystems::intake::IBallDetector> distance_vision_ball_detector
    {
        distance_vision_ball_detector_builder.
        build()
    };
    std::unique_ptr<wisco::robot::ASubsystem> intake_subsystem{std::make_unique<wisco::robot::subsystems::intake::IntakeSubsystem>(pid_intake, distance_vision_ball_detector)};
    robot->addSubsystem(intake_subsystem);

    // Elevator creation
    wisco::robot::subsystems::elevator::PIDElevatorBuilder pid_elevator_builder{};
    std::unique_ptr<wisco::rtos::IClock> elevator_pros_clock{std::make_unique<pros_adapters::ProsClock>()};
    std::unique_ptr<wisco::rtos::IDelayer> elevator_pros_delayer{std::make_unique<pros_adapters::ProsDelayer>()};
    std::unique_ptr<wisco::rtos::IMutex> elevator_pros_mutex{std::make_unique<pros_adapters::ProsMutex>()};
    std::unique_ptr<wisco::rtos::ITask> elevator_pros_task{std::make_unique<pros_adapters::ProsTask>()};
    wisco::control::PID elevator_pid{elevator_pros_clock, ELEVATOR_KP, ELEVATOR_KI, ELEVATOR_KD};
    std::unique_ptr<pros::Motor> elevator_pros_motor_1{std::make_unique<pros::Motor>(ELEVATOR_MOTOR_1_PORT, ELEVATOR_MOTOR_1_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> elevator_pros_motor_1_motor{std::make_unique<pros_adapters::ProsV5Motor>(elevator_pros_motor_1)};
    std::unique_ptr<pros::Motor> elevator_pros_motor_2{std::make_unique<pros::Motor>(ELEVATOR_MOTOR_2_PORT, ELEVATOR_MOTOR_2_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> elevator_pros_motor_2_motor{std::make_unique<pros_adapters::ProsV5Motor>(elevator_pros_motor_2)};
    if (ELEVATOR_ROTATION_SENSOR_PORT)
    {
        std::unique_ptr<pros::Rotation> elevator_pros_rotation{std::make_unique<pros::Rotation>(ELEVATOR_ROTATION_SENSOR_PORT)};
        std::unique_ptr<wisco::io::IRotationSensor> elevator_pros_rotation_sensor{std::make_unique<pros_adapters::ProsRotation>(elevator_pros_rotation)};
        pid_elevator_builder.withRotationSensor(elevator_pros_rotation_sensor);
    }
    std::unique_ptr<wisco::robot::subsystems::elevator::IElevator> pid_elevator
    {
        pid_elevator_builder.
        withClock(elevator_pros_clock)->
        withDelayer(elevator_pros_delayer)->
        withMutex(elevator_pros_mutex)->
        withTask(elevator_pros_task)->
        withPID(elevator_pid)->
        withMotor(elevator_pros_motor_1_motor)->
        withMotor(elevator_pros_motor_2_motor)->
        withInchesPerRadian(ELEVATOR_INCHES_PER_RADIAN)->
        build()
    };
    std::unique_ptr<pros::Distance> elevator_pros_distance{std::make_unique<pros::Distance>(ELEVATOR_DISTANCE_PORT)};
    std::unique_ptr<wisco::io::IDistanceSensor> elevator_pros_distance_sensor{std::make_unique<pros_adapters::ProsDistance>(elevator_pros_distance, ELEVATOR_DISTANCE_CONSTANT, ELEVATOR_DISTANCE_OFFSET)};
    std::unique_ptr<wisco::robot::ASubsystem> elevator_subsystem{std::make_unique<wisco::robot::subsystems::elevator::ElevatorSubsystem>(pid_elevator, elevator_pros_distance_sensor)};
    robot->addSubsystem(elevator_subsystem);

    // Hang creation
    wisco::robot::subsystems::hang::PistonClawBuilder piston_claw_builder{};
    std::unique_ptr<pros::adi::DigitalOut> claw_pros_piston_1{std::make_unique<pros::adi::DigitalOut>(HANG_CLAW_PISTON_1_PORT)};
    std::unique_ptr<wisco::io::IPiston> claw_pros_piston_1_piston{std::make_unique<pros_adapters::ProsPiston>(claw_pros_piston_1, HANG_CLAW_PISTON_1_EXTENDED_STATE)};
    std::unique_ptr<wisco::robot::subsystems::hang::IClaw> piston_claw
    {
        piston_claw_builder.
        withPiston(claw_pros_piston_1_piston)->
        withClosedState(HANG_CLAW_CLOSED_STATE)->
        build()
    };
    wisco::robot::subsystems::hang::PistonToggleArmBuilder piston_toggle_arm_builder{};
    std::unique_ptr<pros::adi::DigitalOut> arm_pros_piston_1{std::make_unique<pros::adi::DigitalOut>(HANG_ARM_PISTON_1_PORT)};
    std::unique_ptr<wisco::io::IPiston> arm_pros_piston_1_piston{std::make_unique<pros_adapters::ProsPiston>(arm_pros_piston_1, HANG_ARM_PISTON_1_EXTENDED_STATE)};
    std::unique_ptr<wisco::robot::subsystems::hang::IToggleArm> piston_arm
    {
        piston_toggle_arm_builder.
        withPiston(arm_pros_piston_1_piston)->
        withUpState(HANG_ARM_UP_STATE)->
        build()
    };
    wisco::robot::subsystems::hang::PistonWinchBuilder piston_winch_builder{};
    std::unique_ptr<pros::adi::DigitalOut> winch_pros_piston_1{std::make_unique<pros::adi::DigitalOut>(HANG_WINCH_PISTON_1_PORT)};
    std::unique_ptr<wisco::io::IPiston> winch_pros_piston_1_piston{std::make_unique<pros_adapters::ProsPiston>(winch_pros_piston_1, HANG_WINCH_PISTON_1_EXTENDED_STATE)};
    std::unique_ptr<wisco::robot::subsystems::hang::IWinch> piston_winch
    {
        piston_winch_builder.
        withPiston(winch_pros_piston_1_piston)->
        withEngagedState(HANG_WINCH_ENGAGED_STATE)->
        build()
    };
    std::unique_ptr<wisco::robot::ASubsystem> hang_subsystem{std::make_unique<wisco::robot::subsystems::hang::HangSubsystem>(piston_claw, piston_arm, piston_winch)};
    robot->addSubsystem(hang_subsystem);

    // Loader creation
    wisco::robot::subsystems::loader::PIDLoaderBuilder pid_loader_builder{};
    std::unique_ptr<wisco::rtos::IClock> loader_pros_clock{std::make_unique<pros_adapters::ProsClock>()};
    std::unique_ptr<wisco::rtos::IDelayer> loader_pros_delayer{std::make_unique<pros_adapters::ProsDelayer>()};
    std::unique_ptr<wisco::rtos::IMutex> loader_pros_mutex{std::make_unique<pros_adapters::ProsMutex>()};
    std::unique_ptr<wisco::rtos::ITask> loader_pros_task{std::make_unique<pros_adapters::ProsTask>()};
    wisco::control::PID loader_pid{loader_pros_clock, LOADER_KP, LOADER_KI, LOADER_KD};
    std::unique_ptr<pros::Motor> loader_pros_motor_1{std::make_unique<pros::Motor>(LOADER_MOTOR_1_PORT, LOADER_MOTOR_1_GEARSET)};
    std::unique_ptr<wisco::io::IMotor> loader_pros_motor_1_motor{std::make_unique<pros_adapters::ProsV5Motor>(loader_pros_motor_1)};
    std::unique_ptr<wisco::robot::subsystems::loader::ILoader> pid_loader
    {
        pid_loader_builder.
        withClock(loader_pros_clock)->
        withDelayer(loader_pros_delayer)->
        withMutex(loader_pros_mutex)->
        withTask(loader_pros_task)->
        withPID(loader_pid)->
        withMotor(loader_pros_motor_1_motor)->
        withMatchLoadPosition(LOADER_LOADED_POSITION)->
        withReadyPosition(LOADER_READY_POSITION)->
        withPositionTolerance(LOADER_POSITION_TOLERANCE)->
        build()
    };
    std::unique_ptr<wisco::robot::ASubsystem> loader_subsystem{std::make_unique<wisco::robot::subsystems::loader::LoaderSubsystem>(pid_loader)};
    robot->addSubsystem(loader_subsystem);

    // Umbrella creation
    wisco::robot::subsystems::umbrella::PistonUmbrellaBuilder piston_umbrella_builder{};
    std::unique_ptr<pros::adi::DigitalOut> umbrella_pros_piston_1{std::make_unique<pros::adi::DigitalOut>(UMBRELLA_PISTON_1_PORT)};
    std::unique_ptr<wisco::io::IPiston> umbrella_pros_piston_1_piston{std::make_unique<pros_adapters::ProsPiston>(umbrella_pros_piston_1, UMBRELLA_PISTON_1_EXTENDED_STATE)};
    std::unique_ptr<wisco::robot::subsystems::umbrella::IUmbrella> piston_umbrella
    {
        piston_umbrella_builder.
        withPiston(umbrella_pros_piston_1_piston)->
        withOutState(UMBRELLA_OUT_STATE)->
        build()
    };
    std::unique_ptr<wisco::robot::ASubsystem> umbrella_subsystem{std::make_unique<wisco::robot::subsystems::umbrella::UmbrellaSubsystem>(piston_umbrella)};
    robot->addSubsystem(umbrella_subsystem);

    // Wings creation
    wisco::robot::subsystems::wings::PistonWingsBuilder piston_wings_builder{};
    std::unique_ptr<pros::adi::DigitalOut> left_wing_pros_piston_1{std::make_unique<pros::adi::DigitalOut>(LEFT_WING_PISTON_1_PORT)};
    std::unique_ptr<wisco::io::IPiston> left_wing_pros_piston_1_piston{std::make_unique<pros_adapters::ProsPiston>(left_wing_pros_piston_1, LEFT_WING_PISTON_1_EXTENDED_STATE)};
    std::unique_ptr<pros::adi::DigitalOut> right_wing_pros_piston_1{std::make_unique<pros::adi::DigitalOut>(RIGHT_WING_PISTON_1_PORT)};
    std::unique_ptr<wisco::io::IPiston> right_wing_pros_piston_1_piston{std::make_unique<pros_adapters::ProsPiston>(right_wing_pros_piston_1, RIGHT_WING_PISTON_1_EXTENDED_STATE)};
    std::unique_ptr<wisco::robot::subsystems::wings::IWings> piston_wings
    {
        piston_wings_builder.
        withLeftPiston(left_wing_pros_piston_1_piston)->
        withRightPiston(right_wing_pros_piston_1_piston)->
        withOutState(WINGS_OUT_STATE)->
        build()
    };
    std::unique_ptr<wisco::robot::ASubsystem> wings_subsystem{std::make_unique<wisco::robot::subsystems::wings::WingsSubsystem>(piston_wings)};
    robot->addSubsystem(wings_subsystem);

    return robot;
}
}
}