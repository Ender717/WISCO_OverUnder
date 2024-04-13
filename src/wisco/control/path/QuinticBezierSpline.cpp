#include "wisco/control/path/QuinticBezierSpline.hpp"

namespace wisco
{
namespace control
{
namespace path
{
std::vector<Point> QuinticBezierSpline::calculate(std::vector<Point>& control_points)
{
    if (control_points.size() == 0 || (control_points.size() - 1) % 3 != 0)
        return std::vector<Point>{};

    // Create the beziers
    std::vector<QuinticBezier> beziers{};
    for (int i{}; i < control_points.size() - 1; i += 3)
    {
        beziers.push_back(QuinticBezier{control_points[i], Point{}, control_points[i + 1], control_points[i + 2], Point{}, control_points[i + 3]});
    }

    // Calculate the smoothing points
    beziers[0].c0 = (beziers[0].k0 + beziers[0].c1) / 2.0;

    for (int i{1}; i < beziers.size(); ++i)
        beziers[i].c0 = (4.0 * beziers[i].k0 - beziers[i - 1].c2 + beziers[i].c1) / 4.0;

    for (int i{}; i < beziers.size() - 1; ++i)
        beziers[i].c3 = 2.0 * beziers[i].k1 - beziers[i + 1].c0;

    beziers[beziers.size() - 1].c3 = (beziers[beziers.size() - 1].k1 + beziers[beziers.size() - 1].c2) / 2.0;

    // Calculate the spline
    std::vector<Point> spline{};
    for (auto& bezier : beziers)
    {
        for (double t{0.0}; t < 1.0; t += 0.02)
        {
            spline.push_back(bezier.calculatePoint(t));
        }
    }
    return spline;
}
} // namespace path
} // namespace control
} // namespace wisco