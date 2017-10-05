#pragma once

#include <iostream>
#include <thread>

//--------------------------------------------------------------------------------------------------
/// @file debug.hpp
/// @brief Debugging macros.
/// @author Susanne van den Elsen
/// @date 2015-2017
//--------------------------------------------------------------------------------------------------


#define _DEBUG
#ifdef _DEBUG
#   define DEBUG(x) do { std::cout << x << std::flush; } while (false)
#   define DEBUGF(class, method, args, other) do { std::cout << class << "::" << method << "(" << args << ")\t" << other; } while (false)
static std::mutex debug_mutex;
#   define DEBUG_SYNC(x) do { std::lock_guard<std::mutex> lock_guard(debug_mutex); DEBUG(x); } while (false)
#   define DEBUGF_SYNC(class, method, args, other) do { std::lock_guard<std::mutex> lock_guard(debug_mutex); DEBUGF(class, method, args, other); } while (false)
#else
#   define DEBUG(x) do { } while (false)
#   define DEBUGF(class, method, args, other) do { } while (false)
#   define DEBUG_SYNC(x) do { } while (false)
#   define DEBUGF_SYNC(class, method, args, other) do { } while (false)
#endif
