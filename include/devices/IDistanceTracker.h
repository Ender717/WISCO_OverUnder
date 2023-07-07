#ifndef I_DISTANCE_TRACKER_H
#define I_DISTANCE_TRACKER_H

namespace devices
{
    /**
     * @brief An interface for devices which track distance in inches
     *
     * @author Nathan Sandvig
     */
    class IDistanceTracker
    {
    public:
        /**
         * @brief Destroy the Distance Tracker object
         *
         */
        virtual ~IDistanceTracker() = default;

        /**
         * @brief Get the Distance
         *
         * @return double The distance
         */
        virtual double getDistance() = 0;

        /**
         * @brief Set the Distance
         *
         * @param distance The new distance
         */
        virtual void setDistance(double distance) = 0;
    };
} // namespace devices

#endif