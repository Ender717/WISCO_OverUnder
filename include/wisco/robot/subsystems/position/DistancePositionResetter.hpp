#ifndef WISCO_ROBOT_SUBSYSTEMS_POSITION_DISTANCE_POSITION_RESETTER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_POSITION_DISTANCE_POSITION_RESETTER_HPP

#include <algorithm>
#include <cmath>
#include <memory>

#include "wisco/io/IDistanceSensor.hpp"
#include "IPositionResetter.hpp"

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
 * @brief Interface for position resetting subsystems
 * @author Nathan Sandvig
 * 
 */
class DistancePositionResetter : public IPositionResetter
{
private:
    /**
     * @brief The coordinate of the near wall
     * 
     */
    static constexpr double NEAR_WALL{0};

    /**
     * @brief The coordinate of the far wall
     * 
     */
    static constexpr double FAR_WALL{144};
    
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

    /**
     * @brief Binds radian values between pi and -pi
     * 
     * @param radians The raw radian value
     * @return double The bound radian value
     */
    double bindRadians(double radians);

public:
    /**
     * @brief Initializes the position resetting system
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the position tracking system
     * 
     */
    void run() override;

    /**
     * @brief Get the reset position for X
     * 
     * @param theta The current robot angle
     * @return double The X reset position
     */
    double getResetX(double theta) override;

    /**
     * @brief Get the reset position for Y
     * 
     * @param theta The current robot angle
     * @return double The Y reset position
     */
    double getResetY(double theta) override;

    /**
     * @brief Get the raw value of the distance sensor
     * 
     * @return double The raw value of the distance sensor
     */
    double getRawValue() override;

    /**
     * @brief Set the distance sensor
     * 
     * @param distance_sensor The distance sensor
     */
    void setDistanceSensor(std::unique_ptr<io::IDistanceSensor>& distance_sensor);

    /**
     * @brief Set the local x-offset
     * 
     * @param local_x The local x-offset
     */
    void setLocalX(double local_x);

    /**
     * @brief Set the local y-offset
     * 
     * @param local_y The local y-offset
     */
    void setLocalY(double local_y);

    /**
     * @brief Set the local angle-offset
     * 
     * @param local_theta The local angle-offset
     */
    void setLocalTheta(double local_theta);
};
} // namespace position
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif
