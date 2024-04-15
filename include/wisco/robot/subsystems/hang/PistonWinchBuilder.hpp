#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_WINCH_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_WINCH_BUILDER_HPP

#include "PistonWinch.hpp"
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
 * @brief Builder for a piston-based winch
 * @author Nathan Sandvig
 * 
 */
class PistonWinchBuilder
{
private:
    /**
     * @brief The pistons for the winch
     * 
     */
    hal::PistonGroup m_pistons{};

    /**
     * @brief The state of the piston group when the winch is engaged
     * 
     */
    bool m_engaged_state{};

public:
    /**
     * @brief Adds a piston to the build
     * 
     * @param piston The piston
     * @return This object for build chaining
     */
    PistonWinchBuilder* withPiston(std::unique_ptr<io::IPiston>& piston);

    /**
     * @brief Adds an engaged state to the build
     * 
     * @param engaged_state The state of the pistons when the winch is engaged
     * @return This object for build chaining
     */
    PistonWinchBuilder* withEngagedState(bool engaged_state);

    /**
     * @brief Builds a piston winch
     * 
     * @return std::unique_ptr<IWinch> The piston winch as a winch interface object
     */
    std::unique_ptr<IWinch> build();
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif