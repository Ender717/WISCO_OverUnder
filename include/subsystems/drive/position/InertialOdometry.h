#ifndef INERTIAL_ODOMETRY_H
#define INERTIAL_ODOMETRY_H

#include <chrono>
#include <memory>

#include "pros/rtos.hpp"

#include "devices/IDistanceTracker.h"
#include "devices/IHeadingTracker.h"
#include "IPositionTracker.h"
#include "subsystems/IRunnable.h"
#include "Position.h"

namespace subsystems
{
    namespace drive
    {
        namespace position
        {
            /**
             * @brief An inertial odometry system
             *
             * @author Nathan Sandvig
             */
            class InertialOdometry : public IPositionTracker, public IRunnable
            {
            private:
                static constexpr int TASK_DELAY{10};
                /**
                 * @brief Starts the system
                 *
                 * @param params The instance of the system
                 */
                static void start(void* params);

                /**
                 * @brief Keeps the system threadsafe
                 *
                 */
                pros::Mutex mutex{};

                /**
                 * @brief Linear distance tracker
                 *
                 */
                std::unique_ptr<devices::IDistanceTracker> linear{nullptr};

                /**
                 * @brief The distance from the linear tracker to the tracking center
                 *
                 */
                double linearOffset{0.0};

                /**
                 * @brief Strafe distance tracker
                 *
                 */
                std::unique_ptr<devices::IDistanceTracker> strafe{nullptr};

                /**
                 * @brief The distance from the strafe tracker to the tracking center
                 *
                 */
                double strafeOffset{0.0};

                /**
                 * @brief Heading tracker
                 *
                 */
                std::unique_ptr<devices::IHeadingTracker> heading{nullptr};

                /**
                 * @brief The current position
                 *
                 */
                Position position{};

                /**
                 * @brief Tracks the elapsed time for duration measurements
                 *
                 */
                std::chrono::steady_clock clock{};

                /**
                 * @brief The time point during the last update
                 *
                 */
                std::chrono::time_point<std::chrono::steady_clock> lastTime{clock.now()};

                /**
                 * @brief The linear distance during the last update
                 *
                 */
                double lastLinear{};

                /**
                 * @brief The strafe distance during the last update
                 *
                 */
                double lastStrafe{};

                /**
                 * @brief The heading during the last update
                 *
                 */
                double lastHeading{};

                /**
                 * @brief Updates the position
                 *
                 */
                void update();

            public:
                /**
                 * @brief Construct a new Inertial Odometry object
                 *
                 * @param linear The linear distance tracker
                 * @param strafe The strafe distance tracker
                 * @param heading The heading tracker
                 */
                InertialOdometry(std::unique_ptr<devices::IDistanceTracker> linear, double linearOffset,
                    std::unique_ptr<devices::IDistanceTracker> strafe, double strafeOffset,
                    std::unique_ptr<devices::IHeadingTracker> heading);

                /**
                 * @brief Initializes the system
                 *
                 */
                void initialize();

                /**
                 * @brief Get the Position
                 *
                 * @return Position The position
                 */
                Position getPosition();

                /**
                 * @brief Set the Position
                 *
                 * @param position The new position
                 */
                void setPosition(Position position);

                /**
                 * @brief Runs the system
                 *
                 */
                void run();
            };
        }
    }
}

#endif