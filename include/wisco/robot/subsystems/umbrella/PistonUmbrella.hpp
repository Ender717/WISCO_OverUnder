#ifndef WISCO_ROBOT_SUBSYSTEMS_UMBRELLA_PISTON_UMBRELLA_HPP
#define WISCO_ROBOT_SUBSYSTEMS_UMBRELLA_PISTON_UMBRELLA_HPP

#include "wisco/hal/PistonGroup.hpp"

#include "IUmbrella.hpp"

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
 * @brief A umbrella controlled using a piston
 * @author Nathan Sandvig
 * 
 */
class PistonUmbrella : public IUmbrella
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
     * @brief Initializes the umbrella
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the umbrella
     * 
     */
    void run() override;

    /**
     * @brief Closes the umbrella
     * 
     */
    void setIn() override;

    /**
     * @brief Opens the umbrella
     * 
     */
    void setOut() override;

    /**
     * @brief Checks if the umbrella is in
     * 
     * @return true The umbrella is in
     * @return false The umbrella is not in
     */
    bool isIn() override;

    /**
     * @brief Checks if the umbrella is out
     * 
     * @return true The umbrella is out
     * @return false The umbrella is not out
     */
    bool isOut() override;

    /**
     * @brief Sets the pistons for the umbrella
     * 
     * @param pistons The pistons for the umbrella
     */
    void setPistons(hal::PistonGroup& pistons);

    /**
     * @brief Sets the state of the pistons when the umbrella is out
     * 
     * @param out_state The state of the pistons when the umbrella is out
     */
    void setOutState(bool out_state);
};
} // namespace umbrella
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif