#ifndef PROS_ADAPTERS_PROS_TOUCH_SCREEN_HPP
#define PROS_ADAPTERS_PROS_TOUCH_SCREEN_HPP

#include <cstdarg>

#include "pros/screen.h"
#include "pros/screen.hpp"

#include "wisco/io/ITouchScreen.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros rtos clock adapter for the wisco rtos IClock interface
 * @author Nathan Sandvig
 * 
 */
class ProsTouchScreen : public wisco::io::ITouchScreen
{
private:
    /**
     * @brief The text format for printing to the screen
     * 
     */
    pros::text_format_e_t m_text_format;

public:
    /**
     * @brief Construct a new Pros Touch Screen object
     * 
     * @param text_format The format for text printed to the screen
     */
    ProsTouchScreen(pros::text_format_e_t text_format);

    /**
     * @brief Prints text to the screen
     * 
     * @param x The x-coordinate to print
     * @param y The y-coordinate to print
     * @param text_format The format string
     * @param ... The arguments for the format string
     */
    void print(uint32_t x, uint32_t y, std::string text_format, ...) override;
};
} // namespace pros_adapters

#endif