#ifndef WISCO_USER_WINGS_WINGS_OPERATOR_HPP
#define WISCO_USER_WINGS_WINGS_OPERATOR_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"
#include "wisco/user/IController.hpp"
#include "wisco/IProfile.hpp"
#include "EWingsControlMode.hpp"

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
 * @brief Namespace for all wings user control components
 * @author Nathan Sandvig
 * 
 */
namespace wings
{

/**
 * @brief Runs the operator-controlled wings settings
 * @author Nathan Sandvig
 * 
 */
class WingsOperator
{
private:
    /**
     * @brief The available states for wings toggles
     * 
     */
    enum class EToggleState
    {
        IN,
        OUT
    };

    /**
     * @brief The name of the wings subsystem
     * 
     */
    static constexpr char WINGS_SUBSYSTEM_NAME[]{"WINGS"};

    /**
     * @brief The command to set the left wing position
     * 
     */
    static constexpr char SET_LEFT_WING_COMMAND[]{"SET LEFT WING"};

    /**
     * @brief The command to set the right wing position
     * 
     */
    static constexpr char SET_RIGHT_WING_COMMAND[]{"SET RIGHT WING"};

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
    EToggleState toggle_state{EToggleState::IN};

    /**
     * @brief The state stored for the left piston for toggle mode
     * 
     */
    EToggleState left_toggle_state{EToggleState::IN};

    /**
     * @brief The state stored for the right piston for toggle mode
     * 
     */
    EToggleState right_toggle_state{EToggleState::IN};

    /**
     * @brief Sets the position of the left wing
     * 
     * @param out True for out, false for in
     */
    void setLeftWing(bool out);

    /**
     * @brief Sets the position of the right wing
     * 
     * @param out True for out, false for in
     */
    void setRightWing(bool out);

    /**
     * @brief Set the wings to a specific position
     * 
     * @param out True for out, false for in
     */
    void setWings(bool out);

    /**
     * @brief Updates the wing position based on a combined hold
     * 
     * @param hold The combined hold digital input
     */
    void updateDualHold(EControllerDigital hold);

    /**
     * @brief Updates the wing position based on a combined split
     * 
     * @param in The combined in digital input
     * @param out The combined out digital input
     */
    void updateDualSplit(EControllerDigital in, EControllerDigital out);

    /**
     * @brief Updates the wing position based on a combined toggle
     * 
     * @param toggle The combined toggle digital input
     */
    void updateDualToggle(EControllerDigital toggle);

    /**
     * @brief Updates the wing position based on a separate hold
     * 
     * @param left_hold The left hold digital input
     * @param right_hold The right hold digital input
     */
    void updateSingleHold(EControllerDigital left_hold, EControllerDigital right_hold);

    /**
     * @brief Updates the wing position based on a separate split
     * 
     * @param left_in The left in digital input
     * @param left_out The left out digital input
     * @param right_in The right in digital input
     * @param right_out The right out digital input
     */
    void updateSingleSplit(EControllerDigital left_in, EControllerDigital left_out, EControllerDigital right_in, EControllerDigital right_out);

    /**
     * @brief Updates the wing position based on a separate toggle
     * 
     * @param left_toggle The left toggle digital input
     * @param right_toggle The right toggle digital input
     */
    void updateSingleToggle(EControllerDigital left_toggle, EControllerDigital right_toggle);

public:
    /**
     * @brief Construct a new Wings Operator object
     * 
     * @param controller The user input controller
     * @param robot The robot to control
     */
    WingsOperator(const std::shared_ptr<user::IController>& controller, 
                   const std::shared_ptr<robot::Robot>& robot);

    /**
     * @brief Set the wings position
     * 
     * @param profile The driver profile
     */
    void setWingsPosition(const std::unique_ptr<IProfile>& profile);
};
} // namespace wings
} // namespace user
} // namespace wisco

#endif