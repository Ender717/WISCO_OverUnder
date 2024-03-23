#ifndef WISCO_USER_DRIVE_OPERATOR_HPP
#define WISCO_USER_DRIVE_OPERATOR_HPP

#include <memory>
#include <string>

#include "wisco/robot/Robot.hpp"
#include "wisco/user/IController.hpp"
#include "EChassisControlMode.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for all user interactive components
 * @author Nathan Sandvig
 * 
 */
namespace user
{

/**
 * @brief Runs the operator-controlled drive voltage settings
 * @author Nathan Sandvig
 * 
 */
class DriveOperator
{
private:
    /**
     * @brief The command to set drive voltage
     * 
     */
    static constexpr char SET_VOLTAGE_COMMAND[]{"SET VOLTAGE"};

    /**
     * @brief Converts controller input to voltage
     * 
     */
    static constexpr double VOLTAGE_CONVERSION{12.0};

    /**
     * @brief The user input controller
     * 
     */
    std::shared_ptr<user::IController> m_controller{};

    /**
     * @brief The robot being controlled
     * 
     */
    std::shared_ptr<robot::Robot> m_robot{};

    /**
     * @brief The name of the drive subsystem being controlled
     * 
     */
    std::string m_drive_name{};

    /**
     * @brief Updates the voltage of the drive subsystem
     * 
     * @param left_voltage The left drive voltage
     * @param right_voltage The right drive voltage
     */
    void updateDriveVoltage(double left_voltage, double right_voltage);

    /**
     * @brief Updates the drive using arcade inputs
     * 
     * @param forward The forward voltage
     * @param turn The turn voltage (positive to the right)
     */
    void updateArcade(double forward, double turn);

    /**
     * @brief Update the drive voltage for single left stick arcade drive
     * 
     */
    void updateSingleArcadeLeft();

    /**
     * @brief Update the drive voltage for single right stick arcade drive
     * 
     */
    void updateSingleArcadeRight();

    /**
     * @brief Update the drive voltage for split stick arcade with left stick forward control
     * 
     */
    void updateSplitArcadeLeft();

    /**
     * @brief Update the drive voltage for split stick arcade with right stick forward control
     * 
     */
    void updateSplitArcadeRight();

    /**
     * @brief Update the drive voltage for tank control
     * 
     */
    void updateTank();

public:
    /**
     * @brief Construct a new Drive Operator object
     * 
     * @param controller The user input controller
     * @param robot The robot to control
     * @param drive_name The name of the drive subsystem
     */
    DriveOperator(const std::shared_ptr<user::IController>& controller, 
                  const std::shared_ptr<robot::Robot>& robot,
                  std::string drive_name);

    /**
     * @brief Set the drive voltage
     * 
     * @param control_mode The control mode of the drive
     */
    void setDriveVoltage(EChassisControlMode control_mode);
};
} // namespace user
} // namespace wisco

#endif