#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_POSITION_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_POSITION_SUBSYSTEM_HPP

#include <memory>

#include "wisco/robot/ASubsystem.hpp"
#include "IPositionTracker.hpp"

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
     * @brief The name of the get position command
     * 
     */
    static constexpr char GET_POSITION_STATE_NAME[]{"GET POSITION"};

    /**
     * @brief The position tracker being adapted
     * 
     */
    std::unique_ptr<IPositionTracker> m_position_tracker{};

public:
    /**
     * @brief Construct a new Position Subsystem object
     * 
     * @param position_tracker The position tracker being adapted
     */
    PositionSubsystem(std::unique_ptr<IPositionTracker>& position_tracker);

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
	 * @param ... The parameters for the command
	 */
	void command(std::string command_name, ...) override;

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