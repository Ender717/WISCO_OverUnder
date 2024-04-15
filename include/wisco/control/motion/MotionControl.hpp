#ifndef WISCO_CONTROL_MOTION_MOTION_CONTROL_HPP
#define WISCO_CONTROL_MOTION_MOTION_CONTROL_HPP

#include <memory>

#include "wisco/control/AControl.hpp"
#include "ITurn.hpp"

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
 * @brief Namespace for basic motion controls
 * @author Nathan Sandvig
 * 
 */
namespace motion
{

/**
 * @brief Control adapter for the motion controller
 * @author Nathan Sandvig
 * 
 */
class MotionControl : public AControl
{
private:
    /**
     * @brief The name of the control
     * 
     */
    static constexpr char CONTROL_NAME[]{"MOTION"};

    /**
     * @brief The name of the turn to angle command
     * 
     */
    static constexpr char TURN_TO_ANGLE_COMMAND_NAME[]{"TURN TO ANGLE"};

    /**
     * @brief The name of the turn to point command
     * 
     */
    static constexpr char TURN_TO_POINT_COMMAND_NAME[]{"TURN TO POINT"};

    /**
     * @brief The name of the pause turn command
     * 
     */
    static constexpr char PAUSE_TURN_COMMAND_NAME[]{"PAUSE TURN"};

    /**
     * @brief The name of the resume turn command
     * 
     */
    static constexpr char RESUME_TURN_COMMAND_NAME[]{"RESUME TURN"};

    /**
     * @brief The name of the turn target reached state
     * 
     */
    static constexpr char TURN_TARGET_REACHED_STATE_NAME[]{"TURN TARGET REACHED"};

    /**
     * @brief The turn controller being adapted
     * 
     */
    std::unique_ptr<ITurn> m_turn{};

public:
    /**
     * @brief Construct a new Motion Control object
     * 
     * @param turn The turn controller being adapted
     */
    MotionControl(std::unique_ptr<ITurn>& turn);

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
} // namespace motion
} // namespace control
} // namespace wisco

#endif