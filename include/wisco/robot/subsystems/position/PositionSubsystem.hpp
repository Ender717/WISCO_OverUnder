#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_POSITION_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_POSITION_SUBSYSTEM_HPP

#include <memory>

#include "wisco/robot/ASubsystem.hpp"
#include "IPositionTracker.hpp"
#include "IPositionResetter.hpp"

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
 * @brief Namespace for all position subsystem classes
 * @author Nathan Sandvig
 * 
 */
namespace position
{

/**
 * @brief Adapter from a position tracker to a robot subsystem
 * @author Nathan Sandvig
 * 
 */
class PositionSubsystem : public ASubsystem
{
private:
    /**
     * @brief The name of the subsystem
     * 
     */
    static constexpr char SUBSYSTEM_NAME[]{"POSITION TRACKER"};

    /**
     * @brief The name of the set position command
     * 
     */
    static constexpr char SET_POSITION_COMMAND_NAME[]{"SET POSITION"};

    /**
     * @brief The name of the set x command
     * 
     */
    static constexpr char SET_X_COMMAND_NAME[]{"SET X"};

    /**
     * @brief The name of the set y command
     * 
     */
    static constexpr char SET_Y_COMMAND_NAME[]{"SET Y"};

    /**
     * @brief The name of the set theta command
     * 
     */
    static constexpr char SET_THETA_COMMAND_NAME[]{"SET THETA"};

    /**
     * @brief The name of the reset x command
     * 
     */
    static constexpr char RESET_X_COMMAND_NAME[]{"RESET X"};

    /**
     * @brief The name of the reset y command
     * 
     */
    static constexpr char RESET_Y_COMMAND_NAME[]{"RESET Y"};

    /**
     * @brief The name of the get position command
     * 
     */
    static constexpr char GET_POSITION_STATE_NAME[]{"GET POSITION"};

    /**
     * @brief The position tracker being adapted
     * 
     */
    std::unique_ptr<IPositionTracker> m_position_tracker{};

    /**
     * @brief The position resetter being adapted
     * 
     */
    std::unique_ptr<IPositionResetter> m_position_resetter{};

public:
    /**
     * @brief Construct a new Position Subsystem object
     * 
     * @param position_tracker The position tracker being adapted
     * @param position_resetter The position resetter being adapted
     */
    PositionSubsystem(std::unique_ptr<IPositionTracker>& position_tracker, 
                      std::unique_ptr<IPositionResetter>& position_resetter);

    /**
	 * @brief Initializes the subsystem
	 *
	 */
	void initialize() override;

    /**
     * @brief Runs the subsystems
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
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif