#include "wisco/control/path/QuinticBezier.hpp"

namespace wisco
{
namespace control
{
namespace path
{
QuinticBezier::QuinticBezier(Point c1, Point c2, Point c3, Point c4, Point c5, Point c6)
    : control_1{c1}, control_2{c2}, control_3{c3}, control_4{c4}, control_5{c5}, control_6{c6}
{

}

Point QuinticBezier::calculatePoint(double t)
{
    return std::pow(1 - t, 5) * control_1
            + 5 * std::pow(1 - t, 4) * t * control_2
            + 10 * std::pow(1 - t, 3) * std::pow(t, 2) * control_3
            + 10 * std::pow(1 - t, 2) * std::pow(t, 3) * control_4
            + 5 * (1 - t) * std::pow(t, 4) * control_5
            + std::pow(t, 5) * control_6;
}
} // namespace path
} // namespace control
} // namespace wisco