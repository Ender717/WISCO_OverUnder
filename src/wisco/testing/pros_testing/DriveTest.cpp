#include "wisco/testing/pros_testing/DriveTest.hpp"

namespace wisco
{
namespace testing
{
namespace pros_testing
{
DriveTest::DriveTest(std::unique_ptr<pros::MotorGroup>& left_drive_motors, 
                     std::unique_ptr<pros::MotorGroup>& right_drive_motors, 
                     std::unique_ptr<pros::Imu>& heading_sensor, 
                     std::unique_ptr<pros::Rotation>& linear_sensor, 
                     double linear_counts_per_inch) :
    m_left_drive_motors{std::move(left_drive_motors)},
    m_right_drive_motors{std::move(right_drive_motors)},
    m_heading_sensor{std::move(heading_sensor)},
    m_linear_sensor{std::move(linear_sensor)},
    m_linear_counts_per_inch{linear_counts_per_inch}
{

}

void DriveTest::initialize()
{
    m_heading_sensor->reset(true);
    m_linear_sensor->reset();
    m_heading_sensor->set_data_rate(5);
    m_linear_sensor->set_data_rate(5);
}

void DriveTest::runLinearTest()
{
    std::string test_output_file_path{FILE_PATH};
    test_output_file_path = test_output_file_path.append(LINEAR_FILE_NAME);
    std::ofstream test_output_file{test_output_file_path};
    if (test_output_file.fail())
        return;

    test_output_file << "linear_velocity,time\n";
    test_output_file.flush();

    if (m_left_drive_motors && m_right_drive_motors && m_heading_sensor && m_linear_sensor)
    {
        m_left_drive_motors->move_voltage(TEST_V * V_TO_MV);
        m_right_drive_motors->move_voltage(TEST_V * V_TO_MV);

        uint32_t start_time{pros::millis()};
        double last_position{m_linear_sensor->get_position() / m_linear_counts_per_inch * INCHES_TO_METERS};
        double last_time{pros::millis() * MILLIS_TO_S};
        while (pros::millis() - start_time < TEST_DURATION)
        {
            double current_position{m_linear_sensor->get_position() / m_linear_counts_per_inch * INCHES_TO_METERS};
            if (current_position != last_position)
            {
                double position_change{current_position - last_position};
                last_position = current_position;

                double current_time{pros::millis() * MILLIS_TO_S};
                double time_change{current_time - last_time};
                last_time = current_time;

                double velocity{position_change / time_change};
                test_output_file << velocity << ',' << current_time << '\n';
                test_output_file.flush();
            }
            pros::delay(1);
        }

        m_left_drive_motors->move_voltage(0);
        m_right_drive_motors->move_voltage(0);
    }
    
    test_output_file.close();
}

void DriveTest::runTurningTest()
{
    std::string test_output_file_path{FILE_PATH};
    test_output_file_path = test_output_file_path.append(TURNING_FILE_NAME);
    std::ofstream test_output_file{test_output_file_path};
    if (test_output_file.fail())
        return;

    test_output_file << "angular_velocity,time\n";
    test_output_file.flush();

    if (m_left_drive_motors && m_right_drive_motors && m_heading_sensor && m_linear_sensor)
    {
        m_left_drive_motors->move_voltage(-TEST_V * V_TO_MV);
        m_right_drive_motors->move_voltage(TEST_V * V_TO_MV);

        uint32_t start_time{pros::millis()};
        double last_rotation{m_heading_sensor->get_rotation() * HEADING_TO_RADIANS};
        double last_time{pros::millis() * MILLIS_TO_S};
        while (pros::millis() - start_time < TEST_DURATION)
        {
            double current_rotation{m_heading_sensor->get_rotation() * HEADING_TO_RADIANS};
            if (current_rotation != last_rotation)
            {
                double rotation_change{current_rotation - last_rotation};
                last_rotation = current_rotation;

                double current_time{pros::millis() * MILLIS_TO_S};
                double time_change{current_time - last_time};
                last_time = current_time;

                double velocity{rotation_change / time_change};
                test_output_file << velocity << ',' << current_time << '\n';
                test_output_file.flush();
            }
            pros::delay(1);
        }

        m_left_drive_motors->move_voltage(0);
        m_right_drive_motors->move_voltage(0);
    }
    
    test_output_file.close();
}
} // namespace pros_testing
} // namespace testing
} // namespace wisco