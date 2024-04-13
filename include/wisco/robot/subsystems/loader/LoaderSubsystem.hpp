#ifndef WISCO_ROBOT_SUBSYSTEMS_LOADER_LOADER_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_LOADER_LOADER_SUBSYSTEM_HPP

#include <memory>

#include "wisco/robot/ASubsystem.hpp"
#include "wisco/robot/subsystems/loader/ILoader.hpp"

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
 * @brief Namespace for loader classes
 * @author Nathan Sandvig
 * 
 */
namespace loader
{

/**
 * @brief The subsystem adapter for loaders
 * @author Nathan Sandvig
 * 
 */
class LoaderSubsystem : public ASubsystem
{
private:
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
     * @brief The loader being adapted
     * 
     */
    std::unique_ptr<ILoader> m_loader{};

public:
    /**
     * @brief Construct a new LOADER Subsystem object
     * 
     * @param loader The loader being adapted
     */
    LoaderSubsystem(std::unique_ptr<ILoader>& loader);
    
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
} // namespace loader
} // namespace subsystems
} // namespace robot
} // namespace robot

#endif