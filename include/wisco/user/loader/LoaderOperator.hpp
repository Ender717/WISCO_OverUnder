#ifndef WISCO_USER_LOADER_LOADER_OPERATOR_HPP
#define WISCO_USER_LOADER_LOADER_OPERATOR_HPP

#include <memory>

#include "wisco/robot/Robot.hpp"
#include "wisco/user/IController.hpp"
#include "wisco/IProfile.hpp"
#include "ELoaderControlMode.hpp"

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
 * @brief Namespace for all loader user control components
 * @author Nathan Sandvig
 * 
 */
namespace loader
{

/**
 * @brief Runs the operator-controlled loader settings
 * @author Nathan Sandvig
 * 
 */
class LoaderOperator
{
private:
    /**
     * @brief The available states for loader toggles
     * 
     */
    enum class EToggleState
    {
        LOAD,
        READY
    };

    /**
     * @brief The name of the subsystem
     * 
     */
    static constexpr char SUBSYSTEM_NAME[]{"LOADER"};

    /**
     * @brief The name of the do load command
     * 
     */
    static constexpr char DO_LOAD_COMMAND_NAME[]{"DO LOAD"};

    /**
     * @brief The name of the do ready command
     * 
     */
    static constexpr char DO_READY_COMMAND_NAME[]{"DO READY"};

    /**
     * @brief The name of the is loaded command
     * 
     */
    static constexpr char IS_LOADED_STATE_NAME[]{"IS LOADED"};

    /**
     * @brief The name of the is ready command
     * 
     */
    static constexpr char IS_READY_STATE_NAME[]{"IS READY"};

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
    EToggleState toggle_state{EToggleState::READY};

    /**
     * @brief Sends a do load command to the loader
     * 
     */
    void doLoad();

    /**
     * @brief Sends a do ready command to the loader
     * 
     */
    void doReady();

    /**
     * @brief Gets the is loaded state from the loader
     * 
     * @return true The loader is loaded
     * @return false The loader is not loaded
     */
    bool isLoaded();

    /**
     * @brief Gets the is ready state from the loader
     * 
     * @return true The loader is ready
     * @return false The loader is not ready
     */
    bool isReady();

    /**
     * @brief Updates the loader position based on a hold
     * 
     * @param hold The hold digital input
     */
    void updateHold(EControllerDigital hold);

    /**
     * @brief Updates the loader position based on a macro
     * 
     * @param toggle The start toggle digital input
     */
    void updateMacro(EControllerDigital toggle);

    /**
     * @brief Updates the loader position based on a single toggle
     * 
     * @param toggle The toggle digital input
     */
    void updateSingleToggle(EControllerDigital toggle);

    /**
     * @brief Updates the loader position based on a split toggle
     * 
     * @param load The load digital input
     * @param ready The ready digital input
     */
    void updateSplitToggle(EControllerDigital load, EControllerDigital ready);

public:
    /**
     * @brief Construct a new Loader Operator object
     * 
     * @param controller The user input controller
     * @param robot The robot to control
     */
    LoaderOperator(const std::shared_ptr<user::IController>& controller, 
                   const std::shared_ptr<robot::Robot>& robot);

    /**
     * @brief Set the loader position
     * 
     * @param profile The driver profile
     */
    void setLoaderPosition(const std::unique_ptr<IProfile>& profile);
};
} // namespace loader
} // namespace user
} // namespace wisco

#endif