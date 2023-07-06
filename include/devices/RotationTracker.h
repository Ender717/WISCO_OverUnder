#ifndef ROTATION_TRACKER_H
#define ROTATION_TRACKER_H

namespace devices
{
    /**
     * @brief An interface for devices which track rotation in radians
     *
     * @author Nathan Sandvig
     */
    class RotationTracker
    {
    public:
        /**
         * @brief Destroy the Rotation Tracker object
         *
         */
        virtual ~RotationTracker() = default;

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