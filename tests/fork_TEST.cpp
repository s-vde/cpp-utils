
#include <fork.hpp>

#include <gtest/gtest.h>


//--------------------------------------------------------------------------------------------------

namespace utils {
namespace sys {
namespace test {

TEST(ForkTest, ForkTestTimeout)
{
   ASSERT_THROW(fork_process("for i in `seq 1 2`; do echo sleeping ; sleep 1 ; done",
                             std::chrono::milliseconds(1000)),
                process_timed_out);
}

TEST(ForkTest, ForkTestNoTimeout)
{
   ASSERT_NO_THROW(fork_process("for i in `seq 1 2`; do echo sleeping ; sleep 1 ; done",
                                std::chrono::milliseconds(3000)));
}

TEST(ForkTest, ForkTestNoTimeoutSubsequent)
{
   ASSERT_NO_THROW(fork_process("for i in `seq 1 2`; do echo sleeping ; sleep 1 ; done",
                                std::chrono::milliseconds(3000)));
   ASSERT_NO_THROW(fork_process("for i in `seq 1 2`; do echo sleeping ; sleep 1 ; done",
                                std::chrono::milliseconds(3000)));
   ASSERT_NO_THROW(fork_process("for i in `seq 1 2`; do echo sleeping ; sleep 1 ; done",
                                std::chrono::milliseconds(3000)));
   ASSERT_NO_THROW(fork_process("for i in `seq 1 2`; do echo sleeping ; sleep 1 ; done",
                                std::chrono::milliseconds(3000)));
}

}   // end namespace test
}   // end namespace sys
}   // end namespace utils
