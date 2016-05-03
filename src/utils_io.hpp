
#ifndef UTILS_IO_HPP_INCLUDED
#define UTILS_IO_HPP_INCLUDED

#include <fstream>
#include <sstream>

/*---------------------------------------------------------------------------75*/
/**
 @file utils_io.hpp
 @brief Declarations and definitions of simple input/output utilities.
 @author Susanne van den Elsen
 @date 2015
 */
/*---------------------------------------------------------------------------++*/

namespace utils
{
    namespace io
    {
        std::istream& skip(std::istream& is, const char c, const unsigned int nr=1);
    
        template<typename T>
        bool read_from_file(const std::string& filename, T& object)
        {
            std::ifstream ifs(filename);
            ifs >> object;
            ifs.close();
            return !ifs.bad();
        }

        template<typename T>
        bool write_to_file(
            const std::string& filename,
            const T& t,
            std::ios_base::openmode mode=std::ios_base::out)
        {
            std::ofstream ofs(filename, mode);
            ofs << t << std::endl;
            ofs.close();
            return !ofs.fail();
        }
    
        template<typename T>
        std::string to_string(const T& t)
        {
            std::stringstream ss{};
            ss << t;
            return ss.str();
        }
    } // end namespace io
} // end namespace utils

#endif
