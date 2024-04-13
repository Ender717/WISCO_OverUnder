#include "wisco/control/path/QuinticBezier.hpp"

namespace wisco
{
namespace control
{
namespace path
{
QuinticBezier::QuinticBezier(Point c1, Point c2, Point c3, Point c4, Point c5, Point c6)
    : k0{c1}, c0{c2}, c1{c3}, c2{c4}, c3{c5}, k1{c6}
{

}

Point QuinticBezier::calculatePoint(double t)
{
    return std::pow(1 - t, 5) * k0
            + 5 * std::pow(1 - t, 4) * t * c0
            + 10 * std::pow(1 - t, 3) * std::pow(t, 2) * c1
            + 10 * std::pow(1 - t, 2) * std::pow(t, 3) * c2
            + 5 * (1 - t) * std::pow(t, 4) * c3
            + std::pow(t, 5) * k1;
}
} // namespace path
} // namespace control
} // namespace wisco