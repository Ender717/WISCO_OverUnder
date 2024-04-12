#ifndef WISCO_ROBOT_SUBSYSTEMS_WINGS_WINGS_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_WINGS_WINGS_SUBSYSTEM_HPP

#include <memory>

#include "wisco/robot/ASubsystem.hpp"
#include "IWings.hpp"

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
 * @brief Namespace for all wings subsystem classes
 * @author Nathan Sandvig
 * 
 */
namespace wings
{

/**
 * @brief The subsystem adapter for wings
 * @author Nathan Sandvig
 * 
 */
class WingsSubsystem : public ASubsystem
{
private:
    /**
     * @brief The name of the subsystem
     * 
     */
    static constexpr char SUBSYSTEM_NAME[]{"WINGS"};

    /**
     * @brief The name of the set left wing command
     * 
     */
    static constexpr char SET_LEFT_WING_COMMAND_NAME[]{"SET LEFT WING"};

    /**
     * @brief The name of the set right wing command
     * 
     */
    static constexpr char SET_RIGHT_WING_COMMAND_NAME[]{"SET RIGHT WING"};

    /**
     * @brief The name of the get left wing state
     * 
     */
    static constexpr char GET_LEFT_WING_STATE_NAME[]{"GET LEFT WING"};

    /**
     * @brief The name of the get right wing state
     * 
     */
    static constexpr char GET_RIGHT_WING_STATE_NAME[]{"GET RIGHT WING"};

    /**
     * @brief The wings being adapted
     * 
     */
    std::unique_ptr<IWings> m_wings{};

public:
    /**
     * @brief Construct a new Wings Subsystem object
     * 
     * @param wings The wings being adapted
     */
    WingsSubsystem(std::unique_ptr<IWings>& wings);

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
} // namespace wings
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif