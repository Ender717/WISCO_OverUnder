#ifndef WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIFFERENTIAL_DRIVE_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_DRIVE_DIFFERENTIAL_DRIVE_SUBSYSTEM_HPP

#include <memory>

#include "wisco/robot/ASubsystem.hpp"

#include "IDifferentialDrive.hpp"

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
 * @brief Namespace for drive classes
 * @author Nathan Sandvig
 * 
 */
namespace drive
{

/**
 * @brief The subsystem adapter for differential drives
 * @author Nathan Sandvig
 * 
 */
class DifferentialDriveSubsystem : public ASubsystem
{
private:
    /**
     * @brief The name of the subsystem
     * 
     */
    static constexpr char SUBSYSTEM_NAME[]{"DIFFERENTIAL DRIVE"};

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
     * @brief The differential drive being adapted
     * 
     */
    std::unique_ptr<IDifferentialDrive> m_differential_drive{};

public:
    /**
     * @brief Construct a new Differential Drive Subsystem object
     * 
     * @param differential_drive The differential drive being adapted
     */
    DifferentialDriveSubsystem(std::unique_ptr<IDifferentialDrive>& differential_drive);
    
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
} // namespace drive
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif