#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_DISTANCE_POSITION_RESETTER_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_DISTANCE_POSITION_RESETTER_BUILDER_HPP

#include "DistancePositionResetter.hpp"

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
 * @brief Builder for distance position resetters
 * @author Nathan Sandvig
 * 
 */
class DistancePositionResetterBuilder
{
private:
    /**
     * @brief The distance sensor used to reset the position
     * 
     */
    std::unique_ptr<io::IDistanceSensor> m_distance_sensor{};

    /**
     * @brief The local x-offset of the distance sensor
     * 
     */
    double m_local_x{};

    /**
     * @brief The local y-offset of the distance sensor
     * 
     */
    double m_local_y{};

    /**
     * @brief The local angle-offset of the distance sensor
     * 
     */
    double m_local_theta{};

public:
    /**
     * @brief Add a distance sensor to the build
     * 
     * @param distance_sensor The distance sensor
     * @return This object for build chaining
     */
    DistancePositionResetterBuilder* withDistanceSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor);

    /**
     * @brief Add a local x-offset to the build
     * 
     * @param local_x The local x-offset
     * @return This object for build chaining
     */
    DistancePositionResetterBuilder* withLocalX(double local_x);

    /**
     * @brief Add a local y-offset to the build
     * 
     * @param local_y The local y-offset
     * @return This object for build chaining
     */
    DistancePositionResetterBuilder* withLocalY(double local_y);

    /**
     * @brief Add a local angle-offset to the build
     * 
     * @param local_theta The local angle-offset
     * @return This object for build chaining
     */
    DistancePositionResetterBuilder* withLocalTheta(double local_theta);

    /**
     * @brief Builds the distance position resetter system
     * 
     * @return std::unique_ptr<IPositionResetter> The distance position resetter as a position resetting interface
     */
    std::unique_ptr<IPositionResetter> build();
};
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif
