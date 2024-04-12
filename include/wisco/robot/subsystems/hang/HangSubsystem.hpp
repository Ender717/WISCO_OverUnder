#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_HANG_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_HANG_SUBSYSTEM_HPP

#include <memory>

#include "wisco/robot/ASubsystem.hpp"

#include "wisco/io/IDistanceSensor.hpp"
#include "IClaw.hpp"
#include "IToggleArm.hpp"
#include "IWinch.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief The namespace that holds all robot classes
 * @author Nathan Sandvig
 *
 */
namespace robot
{

/**
 * @brief Namespace for all robot subsystems
 * @author Nathan Sandvig
 * 
 */
namespace subsystems
{

/**
 * @brief Namespace for hang classes
 * @author Nathan Sandvig
 * 
 */
namespace hang
{

/**
 * @brief The subsystem adapter for hangs
 * @author Nathan Sandvig
 * 
 */
class HangSubsystem : public ASubsystem
{
private:
    /**
     * @brief The name of the subsystem
     * 
     */
    static constexpr char SUBSYSTEM_NAME[]{"HANG"};

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
     * @brief The name of the claw closed state
     * 
     */
    static constexpr char CLAW_CLOSED_STATE_NAME[]{"CLAW CLOSED"};

    /**
     * @brief The name of the claw open state
     * 
     */
    static constexpr char CLAW_OPEN_STATE_NAME[]{"CLAW OPEN"};

    /**
     * @brief The name of the arm down state
     * 
     */
    static constexpr char ARM_DOWN_STATE_NAME[]{"ARM DOWN"};

    /**
     * @brief The name of the arm up state
     * 
     */
    static constexpr char ARM_UP_STATE_NAME[]{"ARM UP"};

    /**
     * @brief The name of the winch engaged state
     * 
     */
    static constexpr char WINCH_ENGAGED_STATE_NAME[]{"WINCH ENGAGED"};

    /**
     * @brief The name of the winch disengaged state
     * 
     */
    static constexpr char WINCH_DISENGAGED_STATE_NAME[]{"WINCH DISENGAGED"};

    /**
     * @brief The name of the cap distance state
     * 
     */
    static constexpr char CAP_DISTANCE_STATE_NAME[]{"CAP DISTANCE"};

    /**
     * @brief The claw being adapted
     * 
     */
    std::unique_ptr<IClaw> m_claw{};

    /**
     * @brief The toggle arm being adapted
     * 
     */
    std::unique_ptr<IToggleArm> m_toggle_arm{};

    /**
     * @brief The winch being adapted
     * 
     */
    std::unique_ptr<IWinch> m_winch{};

    /**
     * @brief The distance sensor being adapted
     * 
     */
    std::unique_ptr<io::IDistanceSensor> m_distance_sensor{};

public:
    /**
     * @brief Construct a new Hang Subsystem object
     * 
     * @param claw The claw being adapted
     * @param toggle_arm The toggle arm being adapted
     * @param winch The winch being adapted
     * @param distance_sensor The distance sensor being adapted
     */
    HangSubsystem(std::unique_ptr<IClaw>& claw, 
                  std::unique_ptr<IToggleArm>& toggle_arm, 
                  std::unique_ptr<IWinch>& winch, 
                  std::unique_ptr<io::IDistanceSensor>& distance_sensor);
	
    /**
	 * @brief Initializes the subsystem
	 *
	 */
	void initialize() override;

	/**
	 * @brief Runs the subsystem
	 * 
	 */
	void run() override;

	/**
	 * @brief Runs a command for the subsystem
	 *
	 * @param command_name The name of the command to run
	 * @param args The parameters for the command
	 */
	void command(std::string command_name, va_list& args) override;

	/**
	 * @brief Gets a state of the subsystem
	 *
	 * @param state_name The name of the state to get
	 * @return void* The current value of that state
	 */
	void* state(std::string state_name) override;
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif