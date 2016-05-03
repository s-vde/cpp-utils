
#ifndef CONTAINER_INPUT_HPP_INCLUDED
#define CONTAINER_INPUT_HPP_INCLUDED

#include <iterator>
#include "debug.hpp"
#include "container_format.hpp" // includes STL containers

/*---------------------------------------------------------------------------75*/
/**
 @file container_input.hpp
 @brief Definition of container input helper class and struct templates and 
 operator>> overloads for supported STL containers and std::pair.
 @author Susanne van den Elsen
 @date 2015
 */
/*---------------------------------------------------------------------------++*/

namespace utils
{
    namespace io
    {
        class container_ctype : public std::ctype<char>
        {
        public:
            
            explicit container_ctype(const container_format_values& format)
            : std::ctype<char>(&mTable[0], false, 0)
            {
                std::copy_n(classic_table(), table_size, mTable);
                mTable[format.mDel] = (mask)space;
                mTable[format.mRight] = (mask)space;
            }
            
        private:
            
            mask mTable[table_size];
            
        }; // end class container_ctype

        /**
         @brief Helper class for checking a prefix of the associated input
         stream against a given container format while reading.
         */
        template<
            typename charT=char,
            typename traits=std::char_traits<charT>
        >
        class istream_format_checker
        {
        public:
            
            // TYPES
            
            /// @brief Type of the associated input stream.
            using istream_type = std::basic_istream<charT,traits>;
            
            // CTORS / DTOR
            
            istream_format_checker(
                istream_type& is,
                const container_format_values& format)
            : mInStream(is)
            , mFormat(format)
            , mNeedLeft(true)
            , mNeedDel(false)
            , mOriginalLoc(mInStream.getloc())
            , mEOC(false)
            {
                /// @note Setting custom locale is only needed when the
                /// delimiters can be read as part of a T value. It
                /// introduces the problem that a sequence of delimiters
                /// in the input is not recognized as an invalid format.
                mInStream.imbue(std::locale(
                    mOriginalLoc,
                    new container_ctype(mFormat))
                );
            }
            
            istream_format_checker(const istream_format_checker&) = default;
            istream_format_checker(istream_format_checker&&) = default;
            ~istream_format_checker() = default;
            
            // OPERATORS
            
            istream_format_checker& operator=(const istream_format_checker&) = default;
            istream_format_checker& operator=(istream_format_checker&&) = default;
            
            //
            
            bool read_left_iff_required()
            {
                return !mNeedLeft || read_left();
            }
            
            bool read_del_iff_required()
            {
                return !mNeedDel || read_del();
            }
            
            /**
             @details Consumes the next character in mInStream, sets mEOC to
             true and returns true iff the next character is equal to
             mFormat.mRight. Otherwise leaves all data members and the
             associated input stream unaffected.
             */
            bool read_right()
            {
                if (static_cast<charT>(mInStream.peek()) == mFormat.mRight) {
                    mInStream.get();
                    mEOC = true;
                    return true;
                }
                return false;
            }
            
            /**
             @details Sets mNeedDel to true and returns true iff reading a
             value from mInStream succeeded.
             */
            template<typename T>
            bool read_value(T& value)
            {
                if (mInStream >> value) {
                    mNeedDel = true;
                    return true;
                }
                DEBUG("read_value() == false");
                return false;
            }
            
            bool eoc() const
            {
                return mEOC;
            }
            
            void close()
            {
                mInStream.imbue(mOriginalLoc);
            }
            
        private:
            
            // DATA MEMBERS

            /// @brief The associated input stream.
            istream_type& mInStream;
            
            container_format_values mFormat;
            
            /// @brief Iff true, the next character needs to equal mFormat.mLeft.
            bool mNeedLeft;
            
            /// @brief Iff true, mFormat.mDel needs to be read before reading a value.
            bool mNeedDel;
            
            /// @brief The locale of the associated input stream at construction.
            std::locale mOriginalLoc;
            
            /// @brief Setting whether end-of-container is reached.
            bool mEOC;
            
            // HELPER FUNCTIONS
            
            /**
             @details Consumes the next character in mInStream, sets mNeedLeft
             to false and returns true iff the next character is equal to
             mFormat.mLeft. Leaves all data members and the associated input 
             stream unaffected otherwise.
             */
            bool read_left()
            {
                if (static_cast<charT>(mInStream.peek()) == mFormat.mLeft) {
                    mInStream.get();
                    mNeedLeft = false;
                    return true;
                }
                DEBUG("read_left() == false: " << static_cast<charT>(mInStream.peek()));
                return false;
            }
            
            /**
             @details Consumes the next character in mInStream and returns true
             iff the next character is equal to mFormat.mDel. Otherwise
             leaves all data members and the associated input stream unaffected.
             */
            bool read_del()
            {
                if (static_cast<charT>(mInStream.peek()) == mFormat.mDel) {
                    mInStream.get();
                    mNeedDel = false;
                    return true;
                }
                DEBUG("read_del() == false: " << static_cast<charT>(mInStream.peek()));
                return false;
            }

        }; // end class template istream_format_checker
        
        // ISTREAM ITERATOR
        
        /**
         @brief An input_iterator that can be used to read containers with 
         element type T from an istream.
         
         @details It behaves like a std::istream_iterator, but requires a
         certain input format.
         
         @tparam T          Element type for the iterator: The type of
                            elements read from the stream.
         @tparam charT      The type of elements the associated basic_istream
                            handles.
         @tparam traits     Character traits for the elements the associated
                            basic_istream handles.
         @tparam Distance   Type to represent the difference between two 
                            iterators (generally a signed integral type).
         
         @note The default template parameter arguments correspond to an
         instantiation that uses a std::istream object as associated stream.
         */
        template<
            typename T,
            typename charT=char,
            typename traits=std::char_traits<charT>,
            typename Distance=std::ptrdiff_t
        >
        class container_istream_iterator
        : public std::iterator<std::input_iterator_tag, T, Distance, const T*, const T&>
        {
        public:
            
            // TYPES
            
            /// @brief Type of the associated input stream.
            using istream_type = std::basic_istream<charT,traits>;
            /// @brief Type of the used istream_format_checker.
            using format_checker_type = istream_format_checker<charT,traits>;
            
            // LIFETIME
            
            /**
             @brief Constructs an end-of-container (eoc) iterator.
             */
            container_istream_iterator()
            : mInStream(nullptr)
            , mValue()
            , mFormatChecker(nullptr) { }
            
            container_istream_iterator(
                istream_type& is,
                const container_format_values& format)
            : mInStream(&is)
            , mValue()
            , mFormatChecker(std::make_shared<format_checker_type>(is, format))
            {
                ++(*this);
            }
            
            container_istream_iterator(const container_istream_iterator&) = default;
            container_istream_iterator(container_istream_iterator&&) = default;
            ~container_istream_iterator() = default;
            
            // OPERATORS
            
            container_istream_iterator& operator=(const container_istream_iterator&) = default;
            container_istream_iterator& operator=(container_istream_iterator&&) = default;
            
            /**
             @brief Compares this container_istream_iterator to rhs.
             @details Two iterators are equal iff they are both eoc iterators 
             or they are both non-eoc iterators.
             */
            bool operator!=(const container_istream_iterator& rhs)
            {
                return
                    !((mInStream == nullptr && rhs.mInStream == nullptr) ||
                      (mInStream != nullptr && rhs.mInStream != nullptr));
            }
            
            /**
             @brief Dereference iterator.
             */
            const T& operator*() const
            {
                return mValue;
            }
            
            /**
             @brief Dereference iterator.
             */
            const T* operator->() const
            {
                return &mValue;
            }

            /**
             @brief Increment iterator position.
             @todo Reading multiple consecutive mDel's should yield an error.
             @todo Reading mFormat.mDel when !mNeedDel should yield an error.
             */
            container_istream_iterator& operator++()
            {
                if (mInStream == nullptr ||
                    /* AND */ (mFormatChecker->read_left_iff_required() &&
                               /* OR */ (mFormatChecker->read_right() ||
                                         /* AND */ (mFormatChecker->read_del_iff_required() &&
                                                    mFormatChecker->read_value(mValue)))))
                { if(mFormatChecker->eoc()) { close(); } }
                else { set_error(); }
                return *this;
            }

        private:
            
            // DATA MEMBERS
            
            /// @brief The associated input stream.
            istream_type* mInStream;
            
            /// @brief The most recently read value.
            T mValue;
            
            /// @brief The used format checker.
            std::shared_ptr<format_checker_type> mFormatChecker;
            
            // HELPER FUNCTIONS
            
            void close()
            {
                mFormatChecker->close();
                mInStream = nullptr;
            }
            
            void set_error()
            {
                mInStream->setstate(std::ios::failbit);
                close();
            }
        }; // end class template container_istream_iterator
        
        // READ_VALUE
        
        template<typename T>
        struct unconst
        {
            using type = T;
        };
        
        template<typename T>
        struct unconst<const T>
        {
            using type = T;
        };
        
        /**
         @details The default read_value::type for a Container is its
         value_type.
         */
        template<typename Container>
        struct read_value
        {
            using type = typename Container::value_type;
        };
        
        /**
         @details The read_value::type for a std::unordered_map<TKey,TVal>
         is a std::pair<unconst<TKey>::type,TVal>, because the template
         function overloading operator<< for std::pair<T1,_> assigns the
         read value to the pair argument's first element, which is not
         allowed if that element is of type const _.
         */
        template<typename TKey, typename TVal>
        struct read_value<std::unordered_map<TKey,TVal>>
        {
            using type = std::pair<typename unconst<TKey>::type,TVal>;
        };
        
    } // end namespace utils.io
} // end namespace utils

namespace std
{
    using namespace utils::io;
    
    /**
     @brief Function template overloading operator>> for supported Containers.

     @details Template instance for Container uses std::copy with
     container_istream_iterators instantiated for the read_value::type
     and container_format associated with Container.
     
     @note The implementation uses std::inserter, which may be slower
     than a specialized inserter (e.g. std::back_inserter) for Container.
     @note This function template cannot be instantiated with containers
     that hold const T, because of the default allocator used for
     insertion.
     */
    template<typename Container>
    typename std::enable_if<
        supported_container<Container>::value,
        std::istream&
    >::type
    operator>>(std::istream& is, Container& C)
    {
        using T = typename read_value<Container>::type;
        container_format<Container> F{};
        if (F.mFormat.mLeft != ' ') { is >> std::ws; }
        std::copy(
            container_istream_iterator<T>(is, F.mFormat),
            container_istream_iterator<T>(),
            std::inserter(C, C.begin())
         );
        return is;
    }
    
    /**
     @brief Function template overloading operator>> for std::pair.
     @note The implementation does not use the container_istream_iterator.
     */
    template<typename T1, typename T2>
    std::istream& operator>>(std::istream& is, std::pair<T1,T2>& P)
    {
        container_format<std::pair<T1,T2>> F{};
        istream_format_checker<char,std::char_traits<char>> C(is, F.mFormat);
        if (C.read_left_iff_required() &&
            C.read_value(P.first) &&
            C.read_del_iff_required() &&
            C.read_value(P.second) &&
            C.read_right())
        { }
        else { is.setstate(std::ios::failbit); }
        return is;
    }
    
} // end namespace std

#endif
