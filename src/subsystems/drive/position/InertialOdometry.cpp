#include "subsystems/drive/position/InertialOdometry.h"

namespace subsystems
{
    namespace drive
    {
        namespace position
        {
            void InertialOdometry::start(void* params)
            {
                InertialOdometry* instance{static_cast<InertialOdometry*>(params)};

                while (instance != nullptr)
                {
                    instance->update();
                    pros::delay(TASK_DELAY);
                }
            }

            InertialOdometry::InertialOdometry(std::unique_ptr<devices::IDistanceTracker> linear, double linearOffset,
                std::unique_ptr<devices::IDistanceTracker> strafe, double strafeOffset,
                std::unique_ptr<devices::IHeadingTracker> heading) :
                linear{std::move(linear)}, linearOffset{linearOffset}, strafe{std::move(strafe)}, strafeOffset{strafeOffset}, heading{std::move(heading)}
            {

            }

            void InertialOdometry::initialize()
            {
                mutex.take();
                lastTime = clock.now();
                lastLinear = linear->getDistance();
                lastStrafe = strafe->getDistance();
                lastHeading = heading->getHeading();
                mutex.give();
            }

            void InertialOdometry::update()
            {
                mutex.take();
                // POSITION CALCULATION
                mutex.give();
            }

            Position InertialOdometry::getPosition()
            {
                mutex.take();
                Position result{position};
                mutex.give();
                return result;
            }

            void InertialOdometry::setPosition(Position position)
            {
                mutex.take();
                this->position = position;
                mutex.give();
            }

            void InertialOdometry::run()
            {
                mutex.take();
                pros::Task task{start, this, "Inertial Odometry Task"};
                mutex.give();
            }
        }
    }
}