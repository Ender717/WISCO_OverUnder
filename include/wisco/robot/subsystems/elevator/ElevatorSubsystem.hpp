#ifndef WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_ELEVATOR_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_ELEVATOR_SUBSYSTEM_HPP

#include <memory>

#include "wisco/robot/ASubsystem.hpp"
#include "wisco/robot/subsystems/elevator/IElevator.hpp"

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
 * @brief Namespace for elevator classes
 * @author Nathan Sandvig
 * 
 */
namespace elevator
{

class ElevatorSubsystem : public ASubsystem
{
private:
    /**
     * @brief The name of the subsystem
     * 
     */
    static constexpr char SUBSYSTEM_NAME[]{"ELEVATOR"};

    /**
     * @brief The name of the set velocity command
     * 
     */
    static constexpr char SET_POSITION_COMMAND_NAME[]{"SET POSITION"};

    /**
     * @brief The name of the get velocity command
     * 
     */
    static constexpr char GET_POSITION_STATE_NAME[]{"GET POSITION"};

    /**
     * @brief The elevator being adapted
     * 
     */
    std::unique_ptr<IElevator> m_elevator{};

public:
    /**
     * @brief Construct a new ELEVATOR Subsystem object
     * 
     * @param elevator The elevator being adapted
     */
    ElevatorSubsystem(std::unique_ptr<IElevator>& elevator);
    
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
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace robot

#endif