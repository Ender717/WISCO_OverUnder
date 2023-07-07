#include "devices/adapters/VexRotationTracker.h"

namespace devices
{
namespace adapters
{
VexRotationTracker::VexRotationTracker(const vex::RotationSensor& rotationSensor) : rotationSensor{rotationSensor}
{

}

double VexRotationTracker::getRotation()
{
    return (rotationSensor.getPosition() * M_PI / 18000.0);
}

void VexRotationTracker::setRotation(double rotation)
{
    rotationSensor.setPosition(rotation * 18000.0 / M_PI);
}
} // namespace adapters
} // namespace devices