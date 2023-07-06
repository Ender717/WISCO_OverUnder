#include "devices/vex/RotationSensor.h"

namespace devices
{
    namespace vex
    {
        RotationSensor::RotationSensor(uint8_t port, bool reversed) : port{port}
        {
            (void)pros::c::rotation_init_reverse(port, reversed);
        }

        RotationSensor::RotationSensor(const RotationSensor& other) : port{other.port}
        {

        }

        RotationSensor::RotationSensor(RotationSensor&& other) : port{std::move(other.port)}
        {

        }

        RotationSensor& RotationSensor::operator=(const RotationSensor& other)
        {
            mutex.take();
            port = other.port;
            mutex.give();
            return *this;
        }

        RotationSensor& RotationSensor::operator=(RotationSensor&& other)
        {
            mutex.take();
            port = std::move(other.port);
            mutex.give();
            return *this;
        }

        void RotationSensor::setPort(uint8_t port)
        {
            mutex.take();
            this->port = port;
            mutex.give();
        }

        uint8_t RotationSensor::getPort()
        {
            mutex.take();
            uint8_t m_port{port};
            mutex.give();
            return m_port;
        }

        int32_t RotationSensor::reset()
        {
            mutex.take();
            int32_t result{pros::c::rotation_reset(port)};
            mutex.give();
            return result;
        }

        int32_t RotationSensor::setDataRate(uint32_t rate)
        {
            mutex.take();
            int32_t result{pros::c::rotation_set_data_rate(port, rate)};
            mutex.give();
            return result;
        }

        int32_t RotationSensor::setPosition(uint32_t position)
        {
            mutex.take();
            int32_t result{pros::c::rotation_set_position(port, position)};
            mutex.give();
            return result;
        }

        int32_t RotationSensor::resetPosition()
        {
            mutex.take();
            int32_t result{pros::c::rotation_reset_position(port)};
            mutex.give();
            return result;
        }

        int32_t RotationSensor::getPosition()
        {
            mutex.take();
            int32_t result{pros::c::rotation_get_position(port)};
            mutex.give();
            return result;
        }

        int32_t RotationSensor::getVelocity()
        {
            mutex.take();
            int32_t result{pros::c::rotation_get_velocity(port)};
            mutex.give();
            return result;
        }

        int32_t RotationSensor::getAngle()
        {
            mutex.take();
            int32_t result{pros::c::rotation_get_angle(port)};
            mutex.give();
            return result;
        }

        int32_t RotationSensor::setReversed(bool value)
        {
            mutex.take();
            int32_t result{pros::c::rotation_set_reversed(port, value)};
            mutex.give();
            return result;
        }

        int32_t RotationSensor::reverse()
        {
            mutex.take();
            int32_t result{pros::c::rotation_reverse(port)};
            mutex.give();
            return result;
        }

        int32_t RotationSensor::getReversed()
        {
            mutex.take();
            int32_t result{pros::c::rotation_get_reversed(port)};
            mutex.give();
            return result;
        }
    } // namespace vex
} // namespace devices
