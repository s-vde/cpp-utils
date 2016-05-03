
#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

#include <iostream>

/*---------------------------------------------------------------------------75*/
/**
 @file debug.hpp
 @brief Debugging macros.
 @author Susanne van den Elsen
 @date 2015
 */
/*---------------------------------------------------------------------------++*/

#ifdef _DEBUG
#   define DEBUG(x) do { std::cout << x; } while (false)
#   define DEBUGNL(x) do { std::cout << x << std::endl; } while (false)
#   define DEBUGF(class, method, args, other) do { std::cout << class << "::" << method << "(" << args << ")\t" << other; } while (false)
#   define DEBUGFNL(class, method, args, other) do { DEBUGF(class, method, args, other << std::endl); } while (false)
#else
#   define DEBUG(x) do { } while (false)
#   define DEBUGNL(x) do { } while (false)
#   define DEBUGF(class, method, args, other) do { } while (false)
#   define DEBUGFNL(class, method, args, other) do { } while (false)
#endif

#endif
