#pragma once

#include <boost/optional.hpp>

#include <signal.h>

#include <chrono>
#include <exception>
#include <string>

//--------------------------------------------------------------------------------------------------
/// @file fork.hpp
/// @author Susanne van den Elsen
/// @date 2017
//--------------------------------------------------------------------------------------------------


namespace utils {
namespace sys {

struct process_timed_out : public std::runtime_error
{
public:
   process_timed_out()
   : std::runtime_error("Process timed out")
   {
   }
};

using timeout_t = std::chrono::milliseconds;

void fork_process(const std::string& process, const boost::optional<timeout_t>& timeout);

}   // end namespace sys
}   // end namespace utils
