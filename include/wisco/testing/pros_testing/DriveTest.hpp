#ifndef WISCO_TESTING_PROS_DRIVE_TEST_HPP
#define WISCO_TESTING_PROS_DRIVE_TEST_HPP

#include <cmath>
#include <fstream>
#include <memory>

#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for all testing functions
 * @author Nathan Sandvig
 * 
 */
namespace testing
{

/**
 * @brief Namespace for pros-based testing functions
 * @author Nathan Sandvig
 * 
 */
namespace pros_testing
{

/**
 * @brief The path for writing all pros testing files
 * 
 */
static constexpr char FILE_PATH[]{"/usd/testing/"};

/**
 * @brief Tests a pros-based drive
 * @author Nathan Sandvig
 * 
 */
class DriveTest
{
private:
    /**
     * @brief The name of the output file for linear drive testing
     * 
     */
    static constexpr char LINEAR_FILE_NAME[]{"drive_linear_test.csv"};

    /**
     * @brief The name of the output file for turning drive testing
     * 
     */
    static constexpr char TURNING_FILE_NAME[]{"drive_turning_test.csv"};

    /**
     * @brief Converts milliseconds to seconds
     * 
     */
    static constexpr double MILLIS_TO_S{1.0 / 1000};

    /**
     * @brief Converts heading to radians
     * 
     */
    static constexpr double HEADING_TO_RADIANS{-M_PI / 18000};

    /**
     * @brief Converts inches to meters
     * 
     */
    static constexpr double INCHES_TO_METERS{2.54 / 100};

    /**
     * @brief Converts Volts to milliVolts
     * 
     */
    static constexpr uint32_t V_TO_MV{1000};

    /**
     * @brief The number of millivolts to use for testing
     * 
     */
    static constexpr uint8_t TEST_V{8};

    /**
     * @brief The duration of the tests in ms
     * 
     */
    static constexpr uint32_t TEST_DURATION{500};

    /**
     * @brief The left drive motors
     * 
     */
    std::unique_ptr<pros::MotorGroup> m_left_drive_motors{};

    /**
     * @brief The right drive motors
     * 
     */
    std::unique_ptr<pros::MotorGroup> m_right_drive_motors{};

    /**
     * @brief The heading sensor
     * 
     */
    std::unique_ptr<pros::Imu> m_heading_sensor{};

    /**
     * @brief The linear distance tracking sensor
     * 
     */
    std::unique_ptr<pros::Rotation> m_linear_sensor{};

    /**
     * @brief The CPI of the linear distance tracking sensor
     * 
     */
    double m_linear_counts_per_inch;

public:
    /**
     * @brief Construct a new Drive Test object
     * 
     * @param left_drive_motors The left drive motors
     * @param right_drive_motors The right drive motors
     * @param heading_sensor The heading sensor
     * @param linear_sensor The linear distance tracking sensor
     * @param linear_counts_per_inch The lienar distance tracking sensor CPI
     */
    DriveTest(std::unique_ptr<pros::MotorGroup>& left_drive_motors, 
              std::unique_ptr<pros::MotorGroup>& right_drive_motors, 
              std::unique_ptr<pros::Imu>& heading_sensor, 
              std::unique_ptr<pros::Rotation>& linear_sensor, 
              double linear_counts_per_inch);

    /**
     * @brief Initializes the drive testing system
     * 
     */
    void initialize();

    /**
     * @brief Runs the linear motion test
     * 
     */
    void runLinearTest();

    /**
     * @brief Runs the turning motion test
     * 
     */
    void runTurningTest();
};

} // namespace pros
} // namespace testing
} // namespace wisco

#endif