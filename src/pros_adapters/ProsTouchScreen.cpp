#include "pros_adapters/ProsTouchScreen.hpp"

namespace pros_adapters
{
ProsTouchScreen::ProsTouchScreen(pros::text_format_e_t text_format) : m_text_format{text_format}
{

}

void ProsTouchScreen::print(uint32_t x, uint32_t y, std::string format, ...)
{
    std::va_list args;
    va_start(args, format);
    pros::screen::print(m_text_format, x, y, format.c_str(), args);
    va_end(args);
}
}