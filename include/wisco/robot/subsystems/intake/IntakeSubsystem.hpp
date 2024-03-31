#ifndef WISCO_ROBOT_SUBSYSTEMS_INTAKE_INTAKE_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_INTAKE_INTAKE_SUBSYSTEM_HPP

#include <memory>

#include "wisco/robot/ASubsystem.hpp"
#include "wisco/robot/subsystems/intake/IIntake.hpp"

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
 * @brief Namespace for intake classes
 * @author Nathan Sandvig
 * 
 */
namespace intake
{

class IntakeSubsystem : public ASubsystem
{
private:
    /**
     * @brief The name of the subsystem
     * 
     */
    static constexpr char SUBSYSTEM_NAME[]{"INTAKE"};

    /**
     * @brief The name of the set velocity command
     * 
     */
    static constexpr char SET_VELOCITY_COMMAND_NAME[]{"SET VELOCITY"};

    /**
     * @brief The name of the set voltage command
     * 
     */
    static constexpr char SET_VOLTAGE_COMMAND_NAME[]{"SET VOLTAGE"};

    /**
     * @brief The name of the get velocity command
     * 
     */
    static constexpr char GET_VELOCITY_STATE_NAME[]{"GET VELOCITY"};

    /**
     * @brief The intake being adapted
     * 
     */
    std::unique_ptr<IIntake> m_intake{};

public:
    /**
     * @brief Construct a new Intake Subsystem object
     * 
     * @param intake The intake being adapted
     */
    IntakeSubsystem(std::unique_ptr<IIntake>& intake);
    
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
} // namespace intake
} // namespace subsystems
} // namespace robot
} // namespace robot

#endif