#ifndef WISCO_CONTROL_BOOMERANG_BOOMERANG_CONTROL_HPP
#define WISCO_CONTROL_BOOMERANG_BOOMERANG_CONTROL_HPP

#include <memory>

#include "wisco/control/AControl.hpp"
#include "IBoomerang.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for control algorithms
 * @author Nathan Sandvig
 * 
 */
namespace control
{

/**
 * @brief Namespace for boomerang controller components
 * @author Nathan Sandvig
 * 
 */
namespace boomerang
{

/**
 * @brief Control adapter for the boomerang controller
 * @author Nathan Sandvig
 * 
 */
class BoomerangControl : public AControl
{
private:
    /**
     * @brief The name of the control
     * 
     */
    static constexpr char CONTROL_NAME[]{"BOOMERANG"};

    /**
     * @brief The name of the go to position command
     * 
     */
    static constexpr char GO_TO_POSITION_COMMAND_NAME[]{"GO TO POSITION"};

    /**
     * @brief The name of the target reached state
     * 
     */
    static constexpr char TARGET_REACHED_STATE_NAME[]{"TARGET REACHED"};

    /**
     * @brief The boomerang controller being adapted
     * 
     */
    std::unique_ptr<IBoomerang> m_boomerang{};

public:
    /**
     * @brief Construct a new Boomerang Control object
     * 
     * @param boomerang The boomerang controller being adapted
     */
    BoomerangControl(std::unique_ptr<IBoomerang>& boomerang);

	/**
	 * @brief Initializes the control
	 *
	 */
	void initialize() override;

	/**
	 * @brief Runs the control
	 * 
	 */
	void run() override;

    /**
     * @brief Pauses the control
     * 
     */
    void pause() override;

    /**
     * @brief Resumes the control
     * 
     */
    void resume() override;

	/**
	 * @brief Runs a command for the control
	 *
	 * @param command_name The name of the command to run
	 * @param args The parameters for the command
	 */
	void command(std::string command_name, va_list& args) override;

	/**
	 * @brief Gets a state of the control
	 *
	 * @param state_name The name of the state to get
	 * @return void* The current value of that state
	 */
	void* state(std::string state_name) override;
};
} // namespace boomerang
} // namespace control
} // namespace wisco

#endif