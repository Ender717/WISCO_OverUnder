#ifndef WISCO_USER_ELEVATOR_OPERATOR_HPP
#define WISCO_USER_ELEVATOR_OPERATOR_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"
#include "wisco/user/IController.hpp"
#include "wisco/IProfile.hpp"
#include "wisco/user/EElevatorControlMode.hpp"

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
 * @brief Runs the operator-controlled elevator position settings
 * @author Nathan Sandvig
 * 
 */
class ElevatorOperator
{
private:
    /**
     * @brief The available states for elevator toggles
     * 
     */
    enum class EToggleState
    {
        IN,
        FIELD,
        MATCH_LOAD,
        OUT
    };

    /**
     * @brief The name of the elevator subsystem
     * 
     */
    static constexpr char ELEVATOR_SUBSYSTEM_NAME[]{"ELEVATOR"};

    /**
     * @brief The command to set elevator position
     * 
     */
    static constexpr char SET_POSITION_COMMAND[]{"SET POSITION"};

    /**
     * @brief The state to get elevator position
     * 
     */
    static constexpr char GET_POSITION_STATE[]{"GET POSITION"};

    /**
     * @brief The in position for the elevator
     * 
     */
    static constexpr double IN_POSITION{0.0};

    /**
     * @brief The field position for the elevator
     * 
     */
    static constexpr double FIELD_POSITION{4.0};

    /**
     * @brief The match loading position for the elevator
     * 
     */
    static constexpr double MATCH_LOAD_POSITION{7.0};

    /**
     * @brief The out position for the elevator
     * 
     */
    static constexpr double OUT_POSITION{20.0};

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
     * @brief Whether or not there is currently manual input
     * 
     */
    bool manual_input{};

    /**
     * @brief Gets the current elevator position
     * 
     * @return double The current elevator position
     */
    double getElevatorPosition();

    /**
     * @brief Updates the position of the elevator subsystem
     * 
     * @param position The elevator position
     */
    void updateElevatorPosition(double position);

    /**
     * @brief Updates the elevator position based on manual control
     * 
     * @param in The digital control for moving the elevator in
     * @param out The digital control for moving the elevator out
     */
    void updateManual(EControllerDigital in, EControllerDigital out);

    /**
     * @brief Updates the elevator position based on preset split control
     * 
     * @param in The digital control for the in position
     * @param field The digital control for the field position
     * @param match_load The digital control for the match load position
     * @param out The digital control for the out position
     */
    void updatePresetSplit(EControllerDigital in, EControllerDigital field, EControllerDigital match_load, EControllerDigital out);

    /**
     * @brief Updates the elevator position based on a toggle
     * 
     * @param toggle The digital control for the toggle
     */
    void updatePresetToggle(EControllerDigital toggle);

    /**
     * @brief Updates the elevator position based on a ladder toggle system
     * 
     * @param in The digital control for the next position inward
     * @param out The digital control for the next position outward
     */
    void updatePresetLadder(EControllerDigital in, EControllerDigital out);

public:
    /**
     * @brief Construct a new Elevator Operator object
     * 
     * @param controller The user input controller
     * @param robot The robot to control
     */
    ElevatorOperator(const std::shared_ptr<user::IController>& controller, 
                   const std::shared_ptr<robot::Robot>& robot);

    /**
     * @brief Set the elevator position
     * 
     * @param profile The driver profile
     */
    void setElevatorPosition(const std::unique_ptr<IProfile>& profile);
};
} // namespace user
} // namespace wisco

#endif