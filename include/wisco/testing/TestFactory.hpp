#ifndef WISCO_TESTING_TEST_FACTORY_HPP
#define WISCO_TESTING_TEST_FACTORY_HPP

#include <memory>
#include <vector>

#include "wisco/testing/pros_testing/DriveTest.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for all testing functions
 * @author Nathan Sandvig
 * 
 */
namespace testing
{

/**
 * @brief Factory to build test classes
 * @author Nathan Sandvig
 * 
 */
class TestFactory
{
private:
    /**
     * @brief The left drive motor ports
     * 
     */
    static const std::vector<int8_t> LEFT_DRIVE_PORTS;

    /**
     * @brief The right drive motor ports
     * 
     */
    static const std::vector<int8_t> RIGHT_DRIVE_PORTS;

    /**
     * @brief The port for the inertial sensor
     * 
     */
    static constexpr int8_t INERTIAL_PORT{9};

    /**
     * @brief The port for the linear distance tracking sensor
     * 
     */
    static constexpr int8_t LINEAR_TRACKING_PORT{8};

    /**
     * @brief The CPI of the linear distance tracking sensor
     * 
     */
    static constexpr double LINEAR_COUNTS_PER_INCH{4696.375};

public:
    /**
     * @brief Create a Drive Test object
     * 
     * @return std::unique_ptr<pros_testing::DriveTest> The drive test object
     */
    static std::unique_ptr<pros_testing::DriveTest> createDriveTest();
};
} // namespace testing
} // namespace wisco

#endif