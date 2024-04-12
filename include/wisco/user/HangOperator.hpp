#ifndef WISCO_USER_HANG_OPERATOR_HPP
#define WISCO_USER_HANG_OPERATOR_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"
#include "wisco/user/IController.hpp"
#include "wisco/IProfile.hpp"
#include "wisco/user/EHangControlMode.hpp"

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
 * @brief Runs the operator-controlled hang settings
 * @author Nathan Sandvig
 * 
 */
class HangOperator
{
private:
    /**
     * @brief The available states for hang toggles
     * 
     */
    enum class EToggleState
    {
        INACTIVE,
        RAISED,
        GRABBED,
        HUNG
    };

    /**
     * @brief The name of the hang subsystem
     * 
     */
    static constexpr char HANG_SUBSYSTEM_NAME[]{"HANG"};

    /**
     * @brief The name of the close claw command
     * 
     */
    static constexpr char CLOSE_CLAW_COMMAND_NAME[]{"CLOSE CLAW"};

    /**
     * @brief The name of the open claw command
     * 
     */
    static constexpr char OPEN_CLAW_COMMAND_NAME[]{"OPEN CLAW"};

    /**
     * @brief The name of the lower arm command
     * 
     */
    static constexpr char LOWER_ARM_COMMAND_NAME[]{"LOWER ARM"};

    /**
     * @brief The name of the raise arm command
     * 
     */
    static constexpr char RAISE_ARM_COMMAND_NAME[]{"RAISE ARM"};

    /**
     * @brief The name of the engage winch command
     * 
     */
    static constexpr char ENGAGE_WINCH_COMMAND_NAME[]{"ENGAGE WINCH"};

    /**
     * @brief The name of the disengage winch command
     * 
     */
    static constexpr char DISENGAGE_WINCH_COMMAND_NAME[]{"DISENGAGE WINCH"};

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
    EToggleState toggle_state{EToggleState::INACTIVE};

    /**
     * @brief Closes the claw
     * 
     */
    void closeClaw();

    /**
     * @brief Opens the claw
     * 
     */
    void openClaw();

    /**
     * @brief Lowers the arm
     * 
     */
    void lowerArm();

    /**
     * @brief Raises the arm
     * 
     */
    void raiseArm();

    /**
     * @brief Engages the winch
     * 
     */
    void engageWinch();

    /**
     * @brief Disengages the winch
     * 
     */
    void disengageWinch();

    /**
     * @brief Sets the hang to the inactive state
     * 
     */
    void setInactiveState();

    /**
     * @brief Sets the hang to the raised state
     * 
     */
    void setRaisedState();

    /**
     * @brief Sets the hang to the grabbed state
     * 
     */
    void setGrabbedState();

    /**
     * @brief Sets the hang to the hung state
     * 
     */
    void setHungState();

    /**
     * @brief Updates the hang state based on preset split control
     * 
     * @param inactive The digital control for the inactive state
     * @param raise The digital control for the raise state
     * @param grab The digital control for the grab state
     * @param hang The digital control for the hang state
     */
    void updatePresetSplit(EControllerDigital inactive, EControllerDigital raise, EControllerDigital grab, EControllerDigital hang);

    /**
     * @brief Updates the hang state based on a toggle
     * 
     * @param toggle The digital control for the toggle
     */
    void updatePresetToggle(EControllerDigital toggle);

    /**
     * @brief Updates the hang state based on a ladder toggle system
     * 
     * @param next The digital control for the next state
     * @param previous The digital control for the next state
     */
    void updatePresetLadder(EControllerDigital next, EControllerDigital previous);

    /**
     * @brief Updates the hang state based on a toggle and a reset
     * 
     * @param toggle The digital control for the toggle
     * @param reset The digital control for the reset
     */
    void updatePresetReset(EControllerDigital toggle, EControllerDigital reset);

public:
    /**
     * @brief Construct a new Hang Operator object
     * 
     * @param controller The user input controller
     * @param robot The robot to control
     */
    HangOperator(const std::shared_ptr<user::IController>& controller, 
                 const std::shared_ptr<robot::Robot>& robot);

    /**
     * @brief Set the hang state
     * 
     * @param profile The driver profile
     */
    void setHangState(const std::unique_ptr<IProfile>& profile);
};
} // namespace user
} // namespace wisco

#endif