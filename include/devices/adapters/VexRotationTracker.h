#ifndef VEX_ROTATION_TRACKER_H
#define VEX_ROTATION_TRACKER_H

#include <cmath>

#include "devices/vex/RotationSensor.h"
#include "devices/IRotationTracker.h"

namespace devices
{
    namespace adapters
    {
        /**
         * @brief An adapter for vex rotation sensors to the rotation tracker interface
         *
         * @author Nathan Sandvig
         */
        class VexRotationTracker : public IRotationTracker
        {
        private:
            /**
             * @brief The rotation sensor being adapted
             *
             */
            vex::RotationSensor rotationSensor{};

        public:
            /**
             * @brief Construct a new Vex Rotation Tracker object
             *
             * @param rotationSensor The rotation sensor being adapted
             */
            explicit VexRotationTracker(const vex::RotationSensor& rotationSensor);

            /**
             * @brief Get the Rotation
             *
             * @return double The rotation
             */
            double getRotation() override;

            /**
             * @brief Set the Rotation
             *
             * @param rotation The new rotation
             */
            void setRotation(double rotation) override;
        };
    } // namespace adapters
} // namespace devices


#endif