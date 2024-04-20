#ifndef WISCO_CONTROL_PATH_PATH_FOLLOWING_CONTROLLER_HPP
#define WISCO_CONTROL_PATH_PATH_FOLLOWING_CONTROLLER_HPP

#include <memory>

#include "wisco/control/AControl.hpp"

#include "IPathFollower.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for control algorithms
 * @author Nathan Sandvig
 * 
 */
namespace control
{

/**
 * @brief Namespace for path components
 * @author Nathan Sandvig
 * 
 */
namespace path
{

/**
 * @brief Control adapter for path following algorithms
 * @author Nathan Sandvig
 * 
 */
class PathFollowingControl : public AControl
{
    /**
     * @brief The name of the control
     * 
     */
    static constexpr char CONTROL_NAME[]{"PATH FOLLOWING"};

    /**
     * @brief The name of the follow path command
     * 
     */
    static constexpr char FOLLOW_PATH_COMMAND_NAME[]{"FOLLOW PATH"};

    /**
     * @brief The name of the set velocity command
     * 
     */
    static constexpr char SET_VELOCITY_COMMAND_NAME[]{"SET VELOCITY"};

    /**
     * @brief The name of the target reached state
     * 
     */
    static constexpr char TARGET_REACHED_STATE_NAME[]{"TARGET REACHED"};

    /**
     * @brief The path following controller being adapted
     * 
     */
    std::unique_ptr<IPathFollower> m_path_follower{};

public:
    /**
     * @brief Construct a new Path Following Control object
     * 
     * @param path_follower The path following controller being adapted
     */
    PathFollowingControl(std::unique_ptr<IPathFollower>& path_follower);

	/**
	 * @brief Initializes the control
	 *
	 */
	void initialize() override;

	/**
	 * @brief Runs the control
	 * 
	 */
	void run() override;

    /**
     * @brief Pauses the control
     * 
     */
    void pause() override;

    /**
     * @brief Resumes the control
     * 
     */
    void resume() override;

	/**
	 * @brief Runs a command for the control
	 *
	 * @param command_name The name of the command to run
	 * @param args The parameters for the command
	 */
	void command(std::string command_name, va_list& args) override;

	/**
	 * @brief Gets a state of the control
	 *
	 * @param state_name The name of the state to get
	 * @return void* The current value of that state
	 */
	void* state(std::string state_name) override;
};
} // namespace path
} // namespace control
} // namespace wisco

#endif