#ifndef WISCO_ROBOT_SUBSYSTEMS_UMBRELLA_PISTON_UMBRELLA_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_UMBRELLA_PISTON_UMBRELLA_BUILDER_HPP

#include "PistonUmbrella.hpp"

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
 * @brief Builder class for piston umbrellas
 * @author Nathan Sandvig
 * 
 */
class PistonUmbrellaBuilder
{
private:
    /**
     * @brief The pistons for the umbrella
     * 
     */
    hal::PistonGroup m_pistons{};

    /**
     * @brief The state of the piston group when the umbrella is out
     * 
     */
    bool m_out_state{};

public:
    /**
     * @brief Adds a piston to the build
     * 
     * @param piston The piston
     * @return This object for build chaining
     */
    PistonUmbrellaBuilder* withPiston(std::unique_ptr<io::IPiston>& piston);

    /**
     * @brief Adds an out state to the build
     * 
     * @param out_state The state of the pistons when the umbrella is out
     * @return This object for build chaining
     */
    PistonUmbrellaBuilder* withOutState(bool out_state);

    /**
     * @brief Builds the piston umbrella
     * 
     * @return std::unique_ptr<IUmbrella> The piston umbrella as an umbrella interface
     */
    std::unique_ptr<IUmbrella> build();
};
} // namespace umbrella
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif