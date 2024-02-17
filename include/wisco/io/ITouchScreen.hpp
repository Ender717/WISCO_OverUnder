#ifndef WISCO_IO_I_TOUCH_SCREEN_HPP
#define WISCO_IO_I_TOUCH_SCREEN_HPP

#include <cstdint>
#include <string>

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for the io types
 * @author Nathan Sandvig
 * 
 */
namespace io
{

/**
 * @brief Interface for touch screens
 * @author Nathan Sandvig
 * 
 */
class ITouchScreen
{
public:
    /**
     * @brief Destroy the ITouchScreen object
     * 
     */
    virtual ~ITouchScreen() = default;

    /**
     * @brief Prints text to the screen
     * 
     * @param x The x-coordinate to print
     * @param y The y-coordinate to print
     * @param text_format The format string
     * @param ... The arguments for the format string
     */
    virtual void print(uint32_t x, uint32_t y, std::string text_format, ...) = 0;
};
} // namespace io
} // namespace wisco

#endif