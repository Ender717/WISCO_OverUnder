#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_CLAW_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_CLAW_BUILDER_HPP

#include "PistonClaw.hpp"
#include "wisco/io/IPiston.hpp"

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
 * @brief Builder for a piston-based claw
 * @author Nathan Sandvig
 * 
 */
class PistonClawBuilder
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
     * @brief Adds a piston to the build
     * 
     * @param pistons The piston
     * @return This object for build chaining
     */
    PistonClawBuilder* withPiston(std::unique_ptr<io::IPiston>& piston);

    /**
     * @brief Adds a closed state to the build
     * 
     * @param closed_state The state of the pistons when the claw is closed
     * @return This object for build chaining
     */
    PistonClawBuilder* withClosedState(bool closed_state);

    /**
     * @brief Builds a piston claw
     * 
     * @return std::unique_ptr<IClaw> The piston claw as a claw interface object
     */
    std::unique_ptr<IClaw> build();
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif