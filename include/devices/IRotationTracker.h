#ifndef I_ROTATION_TRACKER_H
#define I_ROTATION_TRACKER_H

namespace devices
{
/**
 * @brief An interface for devices which track rotation in radians
 *
 * @author Nathan Sandvig
 */
class IRotationTracker
{
public:
    /**
     * @brief Destroy the Rotation Tracker object
     *
     */
    virtual ~IRotationTracker() = default;

    /**
     * @brief Get the Rotation
     *
     * @return double The rotation
     */
    virtual double getRotation() = 0;

    /**
     * @brief Set the Rotation
     *
     * @param rotation The new rotation
     */
    virtual void setRotation(double rotation) = 0;
};
} // namespace devices

#endif