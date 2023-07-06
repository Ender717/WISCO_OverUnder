#include "devices/modules/TrackingWheel.h"

namespace devices
{
    namespace modules
    {
        TrackingWheel::TrackingWheel(std::unique_ptr<RotationTracker>& rotationTracker, double radius) :
            rotationTracker{std::move(rotationTracker)}, radius{radius}
        {

        }

        double TrackingWheel::getDistance()
        {
            return rotationTracker->getRotation() * radius;
        }

        void TrackingWheel::setDistance(double distance)
        {
            rotationTracker->setRotation(distance / radius);
        }
    }
}