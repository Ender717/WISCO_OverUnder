#ifndef WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_ELEVATOR_SUBSYSTEM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_ELEVATOR_ELEVATOR_SUBSYSTEM_HPP

#include <memory>

#include "wisco/io/IDistanceSensor.hpp"
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

/**
 * @brief The subsystem adapter for elevators
 * @author Nathan Sandvig
 * 
 */
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
     * @brief The name of the set voltage command
     * 
     */
    static constexpr char SET_VOLTAGE_COMMAND_NAME[]{"SET VOLTAGE"};

    /**
     * @brief The name of the calibrate command
     * 
     */
    static constexpr char CALIBRATE_COMMAND_NAME[]{"CALIBRATE"};

    /**
     * @brief The name of the get velocity command
     * 
     */
    static constexpr char GET_POSITION_STATE_NAME[]{"GET POSITION"};

    /**
     * @brief The name of the is calibrating state
     * 
     */
    static constexpr char IS_CALIBRATING_STATE_NAME[]{"IS CALIBRATING"};

    /**
     * @brief The name of the cap distance state
     * 
     */
    static constexpr char CAP_DISTANCE_STATE_NAME[]{"CAP DISTANCE"};

    /**
     * @brief The elevator being adapted
     * 
     */
    std::unique_ptr<IElevator> m_elevator{};

    /**
     * @brief The distance sensor being adapted
     * 
     */
    std::unique_ptr<io::IDistanceSensor> m_distance_sensor{};

public:
    /**
     * @brief Construct a new ELEVATOR Subsystem object
     * 
     * @param elevator The elevator being adapted
     * @param distance_sensor The distance sensor being adapted
     */
    ElevatorSubsystem(std::unique_ptr<IElevator>& elevator, std::unique_ptr<io::IDistanceSensor>& distance_sensor);
    
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