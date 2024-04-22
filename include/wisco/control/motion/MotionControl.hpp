#ifndef WISCO_CONTROL_MOTION_MOTION_CONTROL_HPP
#define WISCO_CONTROL_MOTION_MOTION_CONTROL_HPP

#include <memory>

#include "wisco/control/AControl.hpp"
#include "IDriveStraight.hpp"
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
     * @brief The types of motions
     * 
     */
    enum class EMotion
    {
        NONE,
        DRIVE_STRAIGHT,
        TURN
    };

    /**
     * @brief The name of the control
     * 
     */
    static constexpr char CONTROL_NAME[]{"MOTION"};

    /**
     * @brief The name of the drive straight command
     * 
     */
    static constexpr char DRIVE_STRAIGHT_COMMAND_NAME[]{"DRIVE STRAIGHT"};

    /**
     * @brief The name of the set drive straight velocity command
     * 
     */
    static constexpr char SET_DRIVE_STRAIGHT_VELOCITY_COMMAND_NAME[]{"SET DRIVE STRAIGHT VELOCITY"};

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
     * @brief The name of the drive straight target reached state
     * 
     */
    static constexpr char DRIVE_STRAIGHT_TARGET_REACHED_STATE_NAME[]{"DRIVE STRAIGHT TARGET REACHED"};

    /**
     * @brief The name of the turn target reached state
     * 
     */
    static constexpr char TURN_TARGET_REACHED_STATE_NAME[]{"TURN TARGET REACHED"};

    /**
     * @brief The drive straight controller being adapted
     * 
     */
    std::unique_ptr<IDriveStraight> m_drive_straight{};

    /**
     * @brief The turn controller being adapted
     * 
     */
    std::unique_ptr<ITurn> m_turn{};

    /**
     * @brief The current active motion
     * 
     */
    EMotion active_motion{EMotion::NONE};

public:
    /**
     * @brief Construct a new Motion Control object
     * 
     * @param drive_straight The drive straight controller being adapted
     * @param turn The turn controller being adapted
     */
    MotionControl(std::unique_ptr<IDriveStraight>& drive_straight, std::unique_ptr<ITurn>& turn);

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
} // namespace motion
} // namespace control
} // namespace wisco

#endif