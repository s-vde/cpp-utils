
#include "color_output.hpp"

namespace utils
{
    namespace io
    {
        std::string text_color(
            const std::string& input,
            const Color& color,
            const bool bold)
        {
            std::string str = "\033["; // escape
            if (bold) { str += "1;"; }
            str += std::to_string(30 + static_cast<int>(color));
            str += "m";
            str += input;
            str += "\033[0m";
            return str;
        }
    } // end namespace utils.io
} // end namespace utils
