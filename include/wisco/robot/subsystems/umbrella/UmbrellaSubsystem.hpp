#ifndef WISCO_ROBOT_SUBSYSTEMS_UMBRELLA_UMBRELLA_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_UMBRELLA_UMBRELLA_SUBSYSTEM_HPP

#include <memory>

#include "wisco/robot/ASubsystem.hpp"
#include "wisco/robot/subsystems/umbrella/IUmbrella.hpp"

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
 * @brief Namespace for umbrella classes
 * @author Nathan Sandvig
 * 
 */
namespace umbrella
{

/**
 * @brief The subsystem adapter for umbrellas
 * @author Nathan Sandvig
 * 
 */
class UmbrellaSubsystem : public ASubsystem
{
private:
    /**
     * @brief The name of the subsystem
     * 
     */
    static constexpr char SUBSYSTEM_NAME[]{"UMBRELLA"};

    /**
     * @brief The name of the set in command
     * 
     */
    static constexpr char SET_IN_COMMAND_NAME[]{"SET IN"};

    /**
     * @brief The name of the set out command
     * 
     */
    static constexpr char SET_OUT_COMMAND_NAME[]{"SET OUT"};

    /**
     * @brief The name of the is in command
     * 
     */
    static constexpr char IS_IN_STATE_NAME[]{"IS IN"};

    /**
     * @brief The name of the is out command
     * 
     */
    static constexpr char IS_OUT_STATE_NAME[]{"IS OUT"};

    /**
     * @brief The umbrella being adapted
     * 
     */
    std::unique_ptr<IUmbrella> m_umbrella{};

public:
    /**
     * @brief Construct a new UMBRELLA Subsystem object
     * 
     * @param umbrella The umbrella being adapted
     */
    UmbrellaSubsystem(std::unique_ptr<IUmbrella>& umbrella);
    
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
} // namespace umbrella
} // namespace subsystems
} // namespace robot
} // namespace robot

#endif