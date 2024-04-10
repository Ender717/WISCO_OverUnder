#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_CLAW_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_CLAW_HPP

#include "wisco/hal/PistonGroup.hpp"

#include "IClaw.hpp"

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
 * @brief Namespace for hang classes
 * @author Nathan Sandvig
 * 
 */
namespace hang
{

/**
 * @brief A claw controlled using a piston
 * @author Nathan Sandvig
 * 
 */
class PistonClaw : public IClaw
{
private:
    /**
     * @brief The pistons for the claw
     * 
     */
    hal::PistonGroup m_pistons{};

    /**
     * @brief The state of the piston group when the claw is closed
     * 
     */
    bool m_closed_state{};

public:
    /**
     * @brief Initializes the claw
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the claw
     * 
     */
    void run() override;

    /**
     * @brief Closes the claw
     * 
     */
    void close() override;

    /**
     * @brief Opens the claw
     * 
     */
    void open() override;

    /**
     * @brief Checks if the claw is closed
     * 
     * @return true The claw is closed
     * @return false The claw is not closed
     */
    bool isClosed() override;

    /**
     * @brief Checks if the claw is open
     * 
     * @return true The claw is open
     * @return false The claw is not open
     */
    bool isOpen() override;

    /**
     * @brief Sets the pistons for the claw
     * 
     * @param pistons The pistons for the claw
     */
    void setPistons(hal::PistonGroup& pistons);

    /**
     * @brief Sets the state of the pistons when the claw is clsoed
     * 
     * @param closed_state The state of the pistons when the claw is closed
     */
    void setClosedState(bool closed_state);
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif