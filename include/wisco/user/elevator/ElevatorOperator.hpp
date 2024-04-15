#ifndef WISCO_USER_ELEVATOR_ELEVATOR_OPERATOR_HPP
#define WISCO_USER_ELEVATOR_ELEVATOR_OPERATOR_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"
#include "wisco/user/IController.hpp"
#include "wisco/IProfile.hpp"
#include "EElevatorControlMode.hpp"

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
 * @brief Namespace for all elevator user control components
 * @author Nathan Sandvig
 * 
 */
namespace elevator
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
        POLE_HANG,
        PARTNER_HANG
    };

    /**
     * @brief The name of the elevator subsystem
     * 
     */
    static constexpr char ELEVATOR_SUBSYSTEM_NAME[]{"ELEVATOR"};

    /**
     * @brief The name of the hang subsystem
     * 
     */
    static constexpr char HANG_SUBSYSTEM_NAME[]{"HANG"};

    /**
     * @brief The command to set elevator position
     * 
     */
    static constexpr char SET_POSITION_COMMAND[]{"SET POSITION"};

    /**
     * @brief The command to calibrate the elevator
     * 
     */
    static constexpr char CALIBRATE_COMMAND_NAME[]{"CALIBRATE"};

    /**
     * @brief The state to get elevator position
     * 
     */
    static constexpr char GET_POSITION_STATE[]{"GET POSITION"};

    /**
     * @brief The name of the cap distance state
     * 
     */
    static constexpr char CAP_DISTANCE_STATE_NAME[]{"CAP DISTANCE"};

    /**
     * @brief The name of the is calibrating state
     * 
     */
    static constexpr char IS_CALIBRATING_STATE_NAME[]{"IS CALIBRATING"};

    /**
     * @brief The name of the hang arm up state
     * 
     */
    static constexpr char HANG_ARM_UP_STATE_NAME[]{"ARM UP"};

    /**
     * @brief The in position for the elevator
     * 
     */
    static constexpr double IN_POSITION{0.0};

    /**
     * @brief The field position for the elevator
     * 
     */
    static constexpr double FIELD_POSITION{3.0};

    /**
     * @brief The match loading position for the elevator
     * 
     */
    static constexpr double MATCH_LOAD_POSITION{8.0};

    /**
     * @brief The pole hang position for the elevator
     * 
     */
    static constexpr double POLE_HANG_POSITION{16.0};

    /**
     * @brief The partner hang position for the elevator
     * 
     */
    static constexpr double PARTNER_HANG_POSITION{18.0};

    /**
     * @brief The distance to the cap for a pole hang
     * 
     */
    static constexpr double POLE_HANG_DISTANCE{2.0};

    /**
     * @brief The distance within which a cap is considered detected
     * 
     */
    static constexpr double CAP_DETECTED_DISTANCE{5.0};

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
     * @brief Calibrates the elevator
     * 
     */
    void calibrateElevator();

    /**
     * @brief Gets the current elevator position
     * 
     * @return double The current elevator position
     */
    double getElevatorPosition();

    /**
     * @brief Gets the current cap distance
     * 
     * @return double The current cap distance
     */
    double getCapDistance();

    /**
     * @brief Checks if the elevator is calibrating
     * 
     * @return true The elevator is calibrating
     * @return false The elevator is not calibrating
     */
    bool isCalibrating();

    /**
     * @brief Get the hang arm up state
     * 
     * @return true The hang arm is up
     * @return false The hang arm is down
     */
    bool getHangArmUp();

    /**
     * @brief Updates the position of the elevator subsystem
     * 
     * @param position The elevator position
     */
    void updateElevatorPosition(double position);

    /**
     * @brief Updates the pole hang position using the distance sensor
     * 
     */
    void updatePoleHangPosition();

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
     * @param pole_hang The digital control for the pole hang position
     * @param partner_hang The digital control for the partner hang position
     */
    void updatePresetSplit(EControllerDigital in, EControllerDigital field, EControllerDigital match_load, EControllerDigital pole_hang, EControllerDigital partner_hang);

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

    /**
     * @brief Updates the elevator position based on a ladder toggle system with an intake override
     * 
     * @param in The digital control for the next position inward
     * @param out The digital control for the next position outward
     * @param intake The digital control for the intake
     * @param outtake The digital control for the outtake
     */
    void updatePresetLadderIntake(EControllerDigital in, EControllerDigital out, EControllerDigital intake, EControllerDigital outtake);

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
} // namespace elevator
} // namespace user
} // namespace wisco

#endif