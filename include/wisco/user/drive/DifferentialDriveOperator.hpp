#ifndef WISCO_USER_DRIVE_DRIVE_OPERATOR_HPP
#define WISCO_USER_DRIVE_DRIVE_OPERATOR_HPP

#include <memory>

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
 * @brief Namespace for all drive user control components
 * @author Nathan Sandvig
 * 
 */
namespace drive
{

/**
 * @brief Runs the operator-controlled differential drive voltage settings
 * @author Nathan Sandvig
 * 
 */
class DifferentialDriveOperator
{
private:
    /**
     * @brief The name of the differential drive subsystem
     * 
     */
    static constexpr char DIFFERENTIAL_DRIVE_SUBSYSTEM_NAME[]{"DIFFERENTIAL DRIVE"};

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
     */
    DifferentialDriveOperator(const std::shared_ptr<user::IController>& controller, 
                              const std::shared_ptr<robot::Robot>& robot);

    /**
     * @brief Set the drive voltage
     * 
     * @param control_mode The control mode of the drive
     */
    void setDriveVoltage(EChassisControlMode control_mode);
};
} // namespace drive
} // namespace user
} // namespace wisco

#endif