#include "pros_adapters/ProsTouchScreen.hpp"

namespace pros_adapters
{
ProsTouchScreen::ProsTouchScreen(pros::text_format_e_t text_format) : m_text_format{text_format}
{

}

std::string ProsTouchScreen::string_format(const std::string& format, va_list args)
{
    // Determine the required buffer size
    int length = vsnprintf(nullptr, 0, format.c_str(), args);

    // Allocate a buffer of the correct size
    std::string result;
    result.resize(length + 1); // +1 for the null terminator

    // Format the string into the buffer
    vsnprintf(&result[0], result.size(), format.c_str(), args);

    // Remove the null terminator (since std::string handles it)
    result.pop_back();

    return result;
}

void ProsTouchScreen::print(uint32_t x, uint32_t y, std::string format, ...)
{
    std::va_list args;
    va_start(args, format);
    std::string output_string{string_format(format, args)};
    pros::screen::print(m_text_format, x, y, output_string.c_str());
    va_end(args);
}
}