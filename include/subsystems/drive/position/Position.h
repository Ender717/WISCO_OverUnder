#ifndef POSITION_H
#define POSITION_H

namespace subsystems
{
    namespace drive
    {
        namespace position
        {
            /**
             * @brief A position on the field including velocity and acceleration
             *
             * @author Nathan Sandvig
             */
            struct Position
            {
                double x{0.0};
                double y{0.0};
                double theta{0.0};
                double xV{0.0};
                double yV{0.0};
                double thetaV{0.0};
                double xA{0.0};
                double yA{0.0};
                double thetaA{0.0};
            };
        } // namespace position
    } // namespace drive
} // namespace subsystems

#endif