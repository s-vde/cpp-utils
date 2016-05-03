
#ifndef COLOR_OUTPUT_HPP_INCLUDED
#define COLOR_OUTPUT_HPP_INCLUDED

#include <string>

/*---------------------------------------------------------------------------75*/
/**
 @file color_output.hpp
 @brief Definition of enum class Color and declaration of colored terminal 
 output functionality.
 @author Susanne van den Elsen
 @date 2015
 */
/*---------------------------------------------------------------------------++*/

namespace utils
{
    namespace io
    {
        /**
         @brief Enum tagging color codes for terminal printing.
         @see https://en.wikipedia.org/wiki/ANSI_escape_code#graphics
         */
		enum class Color
		{
			BLACK = 0,
			RED = 1,
			GREEN = 2,
			YELLOW = 3,
			BLUE = 4,
			MAGENTA = 5,
			CYAN = 6,
			WHITE = 7
		};
		
        std::string text_color(
            const std::string& input,
            const Color& color,
            const bool bold=true
        );

    } // end namespace utils.io
} // end namespace utils

#endif
