
#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

/*---------------------------------------------------------------------------75*/
/**
 @file debug.hpp
 @brief Error output macros.
 @author Susanne van den Elsen
 @date 2016
 */
/*---------------------------------------------------------------------------++*/

#ifdef _ERROR
#   define ERROR(caller, er) do { std::cerr << "Error in " << caller << ": " << er << std::endl; } while (false)
#else
#   define ERROR(caller, er) do { } while (false)
#endif

#endif
