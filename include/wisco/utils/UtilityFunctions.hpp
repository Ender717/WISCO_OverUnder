#ifndef WISCO_UTILS_UTILITY_FUNCTIONS_HPP
#define WISCO_UTILS_UTILITY_FUNCTIONS_HPP

#include <algorithm>
#include <cmath>

/**
 * @brief Gets the sign of a value
 * 
 * @param value The input value
 * @return int8_t 1 for positive, -1 for negative
 */
int8_t sign(double value);

/**
 * @brief Binds a radian value within the unit circle
 * 
 * @param radians The radian value
 * @return double The bound value from -pi to pi
 */
double bindRadians(double radians);

/**
 * @brief Calculates the angle between two points
 * 
 * @param x1 The x-coordinate of the first point
 * @param y1 The y-coordinate of the first point
 * @param x2 The x-coordinate of the second point
 * @param y2 The y-coordinate of the second point
 * @return double The angle between the two points in radians
 */
double angle(double x1, double y1, double x2, double y2);

/**
 * @brief Calculates the distance between two points
 * 
 * @param x1 The x-coordinate of the first point
 * @param y1 The y-coordinate of the first point
 * @param x2 The x-coordinate of the second point
 * @param y2 The y-coordinate of the second point
 * @return double The distance between the two points
 */
double distance(double x1, double y1, double x2, double y2);

#endif