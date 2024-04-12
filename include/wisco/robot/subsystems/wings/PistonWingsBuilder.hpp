#ifndef WISCO_ROBOT_SUBSYSTEMS_WINGS_PISTON_WINGS_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_WINGS_PISTON_WINGS_BUILDER_HPP

#include "PistonWings.hpp"

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
 * @brief Builder class for the piston wings class
 * @author Nathan Sandvig
 * 
 */
class PistonWingsBuilder
{
private:
    /**
     * @brief The pistons for the left wing
     * 
     */
    hal::PistonGroup m_left_pistons{};

    /**
     * @brief The pistons for the right wing
     * 
     */
    hal::PistonGroup m_right_pistons{};

    /**
     * @brief The state of the pistons when the wings are out
     * 
     */
    bool m_out_state{};

public:
    /**
     * @brief Adds a left wing piston to the build
     * 
     * @param left_piston The left wing piston
     * @return This object for build chaining
     */
    PistonWingsBuilder* withLeftPiston(std::unique_ptr<io::IPiston>& left_piston);

    /**
     * @brief Adds a right wing piston to the build
     * 
     * @param right_piston The right wing piston
     * @return This object for build chaining
     */
    PistonWingsBuilder* withRightPiston(std::unique_ptr<io::IPiston>& right_piston);

    /**
     * @brief Adds an out state to the build
     * 
     * @param out_state The state of the pistons when the wings are out
     * @return This object for build chaining
     */
    PistonWingsBuilder* withOutState(bool out_state);

    /**
     * @brief Builds the piston wings system
     * 
     * @return std::unique_ptr<IWings> The piston wings system as a wings interface
     */
    std::unique_ptr<IWings> build();
};
} // namespace wings
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif