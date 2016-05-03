
#include "utils_io.hpp"

namespace utils
{
    namespace io
    {
        std::istream& skip(std::istream& is, const char c, const unsigned int nr)
        {
            for (unsigned int i = 0; i < nr; ++i) {
                is.ignore(std::numeric_limits<std::streamsize>::max(), is.widen(c));
            }
            return is;
        }
    } // end namespace utils.io
} // end namespace utils
