#ifndef VEX_ROTATION_SENSOR_H
#define VEX_ROTATION_SENSOR_H

#include "pros/rotation.h"
#include "pros/rtos.hpp"

namespace devices
{
    namespace vex
    {
        /**
         * @brief A class for vex rotation sensors
         *
         * @author Nathan Sandvig
         */
        class RotationSensor
        {
        private:
            /**
             * @brief Mutex to keep the rotation sensor thread safe
             *
             */
            pros::Mutex mutex{};

            /**
             * @brief The port for the device
             *
             */
            uint8_t port{0};

        public:
            /**
             * @brief Construct a new RotationSensor object
             *
             */
            RotationSensor() = default;

            /**
             * @brief Construct a new RotationSensor object
             *
             * @param port The port for the sensor
             * @param reversed Whether the sensor is reversed or not
             */
            explicit RotationSensor(uint8_t port, bool reversed);

            /**
             * @brief Construct a new RotationSensor object
             *
             * @param other The RotationSensor to copy
             */
            RotationSensor(const RotationSensor& other);

            /**
             * @brief Construct a new RotationSensor object
             *
             * @param other The RotationSensor to move
             */
            RotationSensor(RotationSensor&& other);

            /**
             * @brief Copy assignment operator
             *
             * @param other The RotationSensor to copy
             * @return RotationSensor& This RotationSensor with the copied values
             */
            RotationSensor& operator=(const RotationSensor& other);

            /**
             * @brief Move assignment operator
             *
             * @param other The RotationSensor to move
             * @return RotationSensor& This RotationSensor with the moved values
             */
            RotationSensor& operator=(RotationSensor&& other);

            /**
             * @brief Set the Port
             *
             * @param port The port
             */
            void setPort(uint8_t port);

            /**
             * @brief Get the Port
             *
             * @return uint8_t The port
             */
            uint8_t getPort();

            /**
             * @brief Resets the absolute position
             *
             * @return int32_t 1 if successful, PROS_ERR if the operation failed
             */
            int32_t reset();

            /**
             * @brief Set the Data Rate
             *
             * @param rate The refresh interval in milliseconds
             * @return int32_t 1 if successful, PROS_ERR if the operation failed
             */
            int32_t setDataRate(uint32_t rate);

            /**
             * @brief Set the Position
             *
             * @param position The position in encoder ticks
             * @return int32_t 1 if successful, PROS_ERR if the operation failed
             */
            int32_t setPosition(uint32_t position);

            /**
             * @brief Reset the sensor position to 0
             *
             * @return int32_t 1 if successful, PROS_ERR if the operation failed
             */
            int32_t resetPosition();

            /**
             * @brief Get the Position
             *
             * @return int32_t The position value in centidegrees if successful, PROS_ERR_F if the operation failed
             */
            int32_t getPosition();

            /**
             * @brief Get the Velocity
             *
             * @return int32_t The velocity value in centidegrees per second if successful, PROS_ERR_F if the operation failed
             */
            int32_t getVelocity();

            /**
             * @brief Get the Angle
             *
             * @return int32_t The angle value in centidegrees if successful, PROS_ERR_F if the operation failed
             */
            int32_t getAngle();

            /**
             * @brief Set the Reversed flag
             *
             * @param value The value for the flag
             * @return int32_t 1 if successful, PROS_ERR if the operation failed
             */
            int32_t setReversed(bool value);

            /**
             * @brief Reversed the rotation sensor
             *
             * @return int32_t 1 if successful, PROS_ERR if the operation failed
             */
            int32_t reverse();

            /**
             * @brief Get the Reversed flag value
             *
             * @return int32_t 1 if reversed, 0 if not reversed, PROS_ERR if the operation failed
             */
            int32_t getReversed();
        };
    } // namespace vex
} // namespace devices

#endif