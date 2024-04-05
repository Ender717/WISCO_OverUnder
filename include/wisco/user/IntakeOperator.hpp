#ifndef WISCO_USER_INTAKE_OPERATOR_HPP
#define WISCO_USER_INTAKE_OPERATOR_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"
#include "wisco/user/IController.hpp"
#include "wisco/IProfile.hpp"
#include "wisco/user/EIntakeControlMode.hpp"

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
     * @brief The available states for intake toggles
     * 
     */
    enum class EToggleState
    {
        OFF,
        IN,
        OUT
    };

    /**
     * @brief The name of the intake subsystem
     * 
     */
    static constexpr char INTAKE_SUBSYSTEM_NAME[]{"INTAKE"};

    /**
     * @brief The command to set intake voltage
     * 
     */
    static constexpr char SET_VOLTAGE_COMMAND[]{"SET VOLTAGE"};

    /**
     * @brief The voltage to run the intake at
     * 
     */
    static constexpr double VOLTAGE_SETTING{12.0};

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
     * @brief The state stored for toggle mode
     * 
     */
    EToggleState toggle_state{EToggleState::OFF};

    /**
     * @brief Updates the voltage of the intake subsystem
     * 
     * @param voltage The intake voltage
     */
    void updateIntakeVoltage(double voltage);

    /**
     * @brief Updates the intake voltage based on toggle state
     * 
     */
    void updateToggleVoltage();

    /**
     * @brief Update the voltage for single button toggle
     * 
     */
    void updateSingleToggle(EControllerDigital toggle);

    /**
     * @brief Update the voltage for split button hold
     * 
     */
    void updateSplitHold(EControllerDigital in, EControllerDigital out);

    /**
     * @brief Update the voltage for split button toggle
     * 
     */
    void updateSplitToggle(EControllerDigital in, EControllerDigital out);

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
     * @param profile The driver profile
     */
    void setIntakeVoltage(const std::unique_ptr<IProfile>& profile);
};
} // namespace user
} // namespace wisco

#endif