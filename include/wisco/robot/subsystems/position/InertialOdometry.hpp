#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_INERTIAL_ODOMETRY_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_INERTIAL_ODOMETRY_HPP

#include "IPositionTracker.hpp"

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
 * @brief Namespace for all position subsystem classes
 * @author Nathan Sandvig
 * 
 */
namespace position
{

/**
 * @brief An odometry system based on a heading sensor with two distance tracking sensors
 * @author Nathan Sandvig
 * 
 */
class InertialOdometry : public IPositionTracker
{
private:
    
};
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif