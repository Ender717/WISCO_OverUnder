#ifndef WISCO_ROBOT_SUBSYSTEMS_WINGS_PISTON_WINGS_HPP
#define WISCO_ROBOT_SUBSYSTEMS_WINGS_PISTON_WINGS_HPP

#include "wisco/hal/PistonGroup.hpp"

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
 * @brief Wings controlled using pistons
 * @author Nathan Sandvig
 * 
 */
class PistonWings : public IWings
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
     * @brief Initializes the wings
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the wings
     * 
     */
    void run() override;

    /**
     * @brief Sets the position of the left wing
     * 
     * @param out True for out, false for in
     */
    void setLeftWing(bool out) override;

    /**
     * @brief Sets the position of the right wing
     * 
     * @param out True for out, false for in
     */
    void setRightWing(bool out) override;

    /**
     * @brief Gets the position of the left wing
     * 
     * @return true The wing is out
     * @return false The wing is in
     */
    bool getLeftWing() override;

    /**
     * @brief Gets the position of the right wing
     * 
     * @return true The wing is out
     * @return false The wing is in
     */
    bool getRightWing() override;

    /**
     * @brief Sets the left wing pistons
     * 
     * @param left_pistons The left wing pistons
     */
    void setLeftPistons(hal::PistonGroup& left_pistons);

    /**
     * @brief Sets the right wing pistons
     * 
     * @param right_pistons The right wing pistons
     */
    void setRightPistons(hal::PistonGroup& right_pistons);

    /**
     * @brief Sets the state of the pistons when the wings are out
     * 
     * @param out_state The state of the pistons when the wings are out
     */
    void setOutState(bool out_state);
};
} // namespace wings
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif