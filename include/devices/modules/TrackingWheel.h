#ifndef TRACKING_WHEEL_H
#define TRACKING_WHEEL_H

#include <memory>

#include "devices/DistanceTracker.h"
#include "devices/RotationTracker.h"

namespace devices
{
    namespace modules
    {
        /**
         * @brief A tracking wheel that converts rotation to distance
         *
         * @author Nathan Sandvig
         */
        class TrackingWheel : public DistanceTracker
        {
        private:
            /**
             * @brief The rotation tracker on the wheel
             *
             */
            std::unique_ptr<RotationTracker> rotationTracker{nullptr};

            /**
             * @brief The radius of the wheel
             *
             */
            double radius{0.0};

        public:
            /**
             * @brief Construct a new Tracking Wheel object
             *
             * @param rotationTracker The rotation tracker on the wheel
             * @param radius The radius of the wheel
             */
            TrackingWheel(std::unique_ptr<RotationTracker>& rotationTracker, double radius);

            /**
             * @brief Get the Distance
             *
             * @return double The distance
             */
            double getDistance() override;

            /**
             * @brief Set the Distance
             *
             * @param distance The new distance
             */
            void setDistance(double distance) override;
        };
    } // namespace modules
} // namespace devices


#endif