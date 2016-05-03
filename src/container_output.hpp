
#ifndef CONTAINER_OUTPUT_HPP_INCLUDED
#define CONTAINER_OUTPUT_HPP_INCLUDED

#include <iterator>
#include "container_format.hpp" // includes STL containers

/*---------------------------------------------------------------------------75*/
/**
 @file container_output.hpp
 @brief Definition of container output helper class templates and operator<< 
 overloads for supported STL containers and std::pair.
 @author Susanne van den Elsen
 @date 2015
 */
/*---------------------------------------------------------------------------++*/

namespace utils
{
    namespace io
    {
        // OSTREAM ITERATOR
        
        /**
         @brief An output_iterator that can be used to copy containers with 
         element type T to an ostream.
         
         @details It behaves like a std::ostream_iterator, but does not
         produce a trailing delimiter after copying the last element of the
         container.
         
         @tparam T      Element type for the iterator: The type of elements 
                        inserted into the stream.
         @tparam charT  The type of elements the associated basic_ostream 
                        handles.
         @tparam traits Character traits for the elements the associated
                        basic_ostream handles.
         
         @note The default template parameter arguments correspond to an
         instantiation that uses a std::ostream object as associated stream.
         */
        template<
            typename T,
            typename charT=char,
            typename traits=std::char_traits<charT>
        >
        class container_ostream_iterator
        : public std::iterator<std::output_iterator_tag, void, void, void, void>
        {
        public:
            
            // TYPES
            
            /// @brief Type of the associated output stream.
            using ostream_type = std::basic_ostream<charT,traits>;
            
            // CTORS / DTOR
            
            container_ostream_iterator(ostream_type& os, const charT* delim=0)
            : mOutStream(os)
            , mDelim(delim)
            , mOutputDelim(false) { }
            
            container_ostream_iterator(const container_ostream_iterator&) = default;
            container_ostream_iterator(container_ostream_iterator&&) = default;
            ~container_ostream_iterator() = default;
            
            // OPERATORS
            
            container_ostream_iterator& operator=(const container_ostream_iterator&) = delete;
            container_ostream_iterator& operator=(container_ostream_iterator&&) = delete;
            
            container_ostream_iterator<T>& operator=(const T& t)
            {
                if (mOutputDelim)   { mOutStream << *mDelim;    }
                else                { mOutputDelim = true;      }
                mOutStream << t;
                return *this;
            }
            
            /**
             @brief Dereference iterator.
             */
            container_ostream_iterator<T>& operator*()
            {
                return *this;
            }
            
            /**
             @brief Increment iterator position.
             */
            container_ostream_iterator<T>& operator++()
            {
                return *this;
            }
            
        private:
            
            // DATA MEMBERS
            
            /// @brief The associated output stream.
            ostream_type& mOutStream;
            
            /// @brief Delimiter to produce between two elements.
            const charT* mDelim;
            
            /// @brief Whether or not to produce mDelim before writing the next element.
            bool mOutputDelim = false;
            
        }; // end class template container_ostream_iterator

    } // end namespace utils.io
} // end namespace utils

namespace std
{
    using namespace utils::io;
    
    /**
     @brief Function template overloading operator<< for supported Containers.
     @details Template instance for Container uses std::copy with an
     container_ostream_iterator instantiated for Container::value_type.
     */
    template<typename Container>
    typename std::enable_if<
        supported_container<Container>::value,
        std::ostream&
    >::type
    operator<<(std::ostream& os, const Container& C)
    {
        using T = typename Container::value_type;
        container_format<Container> F{};
        os << F.mFormat.mLeft;
        std::copy(
            C.begin(),
            C.end(),
            container_ostream_iterator<T>(os, &(F.mFormat.mDel))
        );
        os << F.mFormat.mRight;
        return os;
    }
    
    /**
     @brief Function template overloading operator<< for std::pair.
     @note The implementation does not use the container_ostream_iterator.
     */
    template<typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& P)
    {
        container_format<std::pair<T1,T2>> F{};
        os  << F.mFormat.mLeft
            << P.first
            << F.mFormat.mDel
            << P.second
            << F.mFormat.mRight;
        return os;
    }
    
} // end namespace std

#endif
