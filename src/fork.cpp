
#include "fork.hpp"

#include <signal.h>


namespace utils {
namespace sys {

void fork_process(const std::string& process, const boost::optional<timeout_t>& timeout)
{
   pid_t pid = fork();
   std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

   // Child process
   if (pid == 0)
   {
      setpgid(getpid(), getpid());
      system(process.c_str());
      exit(EXIT_SUCCESS);
   }

   // Parent process
   else
   {
      int status;
      while (true)
      {
         if (const pid_t child_status = waitpid(pid, &status, WNOHANG) == pid && WIFEXITED(status))
            return;
            
         // Check for timeout
         if (timeout)
         {
            const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now() - start);
            
            if (elapsed >= *timeout)
            {
               kill(-pid, SIGKILL);
               throw process_timed_out();
            }
         }
      }
   }
}

}   // end namespace sys
}   // end namespace utils
