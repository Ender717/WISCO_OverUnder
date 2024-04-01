#ifndef WISCO_USER_DRIVE_OPERATOR_HPP
#define WISCO_USER_DRIVE_OPERATOR_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"
#include "wisco/user/IController.hpp"
#include "EIntakeControlMode.hpp"

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
 * @brief Runs the operator-controlled intake voltage settings
 * @author Nathan Sandvig
 * 
 */
class IntakeOperator
{
private:
    /**
     * @brief The name of the differential drive subsystem
     * 
     */
    static constexpr char INTAKE_SUBSYSTEM_NAME[]{"INTAKE"};

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
     * @brief Updates the voltage of the intake subsystem
     * 
     * @param voltage The intake voltage
     */
    void updateIntakeVoltage(double voltage);

    /**
     * @brief Update the drive voltage for single left stick arcade drive
     * 
     */
    void updateSingleToggle();

    /**
     * @brief Update the drive voltage for single right stick arcade drive
     * 
     */
    void updateSplitHold();

    /**
     * @brief Update the drive voltage for split stick arcade with left stick forward control
     * 
     */
    void updateSplitToggle();

public:
    /**
     * @brief Construct a new Intake Operator object
     * 
     * @param controller The user input controller
     * @param robot The robot to control
     */
    IntakeOperator(const std::shared_ptr<user::IController>& controller, 
                              const std::shared_ptr<robot::Robot>& robot);

    /**
     * @brief Set the intake voltage
     * 
     * @param control_mode The control mode of the intake
     */
    void setIntakeVoltage(EIntakeControlMode control_mode);
};
} // namespace user
} // namespace wisco

#endif