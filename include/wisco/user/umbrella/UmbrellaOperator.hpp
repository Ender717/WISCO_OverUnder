#ifndef WISCO_USER_UMBRELLA_UMBRELLA_OPERATOR_HPP
#define WISCO_USER_UMBRELLA_UMBRELLA_OPERATOR_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"
#include "wisco/user/IController.hpp"
#include "wisco/IProfile.hpp"
#include "EUmbrellaControlMode.hpp"

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
 * @brief Namespace for all umbrella user control components
 * @author Nathan Sandvig
 * 
 */
namespace umbrella
{

/**
 * @brief Runs the operator-controlled umbrella settings
 * @author Nathan Sandvig
 * 
 */
class UmbrellaOperator
{
private:
    /**
     * @brief The available states for umbrella toggles
     * 
     */
    enum class EToggleState
    {
        IN,
        OUT
    };

    /**
     * @brief The name of the umbrella subsystem
     * 
     */
    static constexpr char UMBRELLA_SUBSYSTEM_NAME[]{"UMBRELLA"};

    /**
     * @brief The command to set in
     * 
     */
    static constexpr char SET_IN_COMMAND[]{"SET IN"};

    /**
     * @brief The command to set out
     * 
     */
    static constexpr char SET_OUT_COMMAND[]{"SET OUT"};

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
     * @brief Sets the umbrella in
     * 
     */
    void setIn();

    /**
     * @brief Sets the umbrella out
     * 
     */
    void setOut();

    /**
     * @brief Updates the umbrella position based on a hold
     * 
     * @param hold The hold digital input
     */
    void updateHold(EControllerDigital hold);

    /**
     * @brief Updates the umbrella position based on a split
     * 
     * @param in The in digital input
     * @param out The out digital input
     */
    void updateSplit(EControllerDigital in, EControllerDigital out);

    /**
     * @brief Updates the umbrella position based on a toggle
     * 
     * @param toggle The toggle digital input
     */
    void updateToggle(EControllerDigital toggle);

public:
    /**
     * @brief Construct a new Umbrella Operator object
     * 
     * @param controller The user input controller
     * @param robot The robot to control
     */
    UmbrellaOperator(const std::shared_ptr<user::IController>& controller, 
                     const std::shared_ptr<robot::Robot>& robot);

    /**
     * @brief Set the umbrella position
     * 
     * @param profile The driver profile
     */
    void setUmbrellaPosition(const std::unique_ptr<IProfile>& profile);
};
} // namespace umbrella
} // namespace user
} // namespace wisco

#endif