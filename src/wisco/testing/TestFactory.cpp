#include "wisco/testing/TestFactory.hpp"

namespace wisco
{
namespace testing
{
const std::vector<int8_t> TestFactory::LEFT_DRIVE_PORTS{11, 12, -13, -14};
const std::vector<int8_t> TestFactory::RIGHT_DRIVE_PORTS{17, 18, -19, -20};

std::unique_ptr<pros_testing::DriveTest> TestFactory::createDriveTest()
{
    std::unique_ptr<pros::MotorGroup> left_drive_motors{std::make_unique<pros::MotorGroup>(LEFT_DRIVE_PORTS)};
    std::unique_ptr<pros::MotorGroup> right_drive_motors{std::make_unique<pros::MotorGroup>(RIGHT_DRIVE_PORTS)};
    std::unique_ptr<pros::Imu> heading_sensor{std::make_unique<pros::Imu>(INERTIAL_PORT)};
    std::unique_ptr<pros::Rotation> linear_tracking_sensor{std::make_unique<pros::Rotation>(LINEAR_TRACKING_PORT)};

    return std::make_unique<pros_testing::DriveTest>(left_drive_motors, right_drive_motors, heading_sensor, linear_tracking_sensor, LINEAR_COUNTS_PER_INCH);
}
} // namespace testing
} // namespace wisco