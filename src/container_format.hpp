
#ifndef CONTAINER_FORMAT_HPP_INCLUDED
#define CONTAINER_FORMAT_HPP_INCLUDED

#include <locale>
#include <type_traits>
// Containers
#include <forward_list>
#include <set>
#include <unordered_map>
#include <vector>

/*---------------------------------------------------------------------------75*/
/**
 @file container_format.hpp
 @brief Definition of formatting structs for container input/output, 
 templates to declare STL containers supported or not supported and associate 
 them with a default container format.
 @author Susanne van den Elsen
 @date 2015
 */
/*---------------------------------------------------------------------------++*/

namespace utils
{
    namespace io
    {
        // FORMAT
        
        /**
         @brief Input/Output format structure for containers.
         */
        struct container_format_values
        {
            char mLeft;
            char mRight;
            char mDel;
        }; // end struct ContainerFormat
        
        template<typename Container>
        struct container_format
        {
            static container_format_values mFormat;
        };
        
        // SUPPORTED CONTAINERS
        
        /**
         @brief By default, T is not a supported container.
         */
        template<typename T> struct supported_container : public std::false_type { };
		
		// std::forward_list
		
		template<typename T, typename Allocator>
		struct supported_container<std::forward_list<T, Allocator>> : public std::true_type {};
		
		/**
		 @brief Default format for std::forward_list is [el1,...,eln].
		 */
		template<typename T, typename Allocator>
		struct container_format<std::forward_list<T, Allocator>>
		{
			const container_format_values mFormat;
			container_format() : mFormat({ '[', ']', ',' }) { }
		};
		
        // std::pair
		
        /**
         @brief Default format for std::pair is (el1,el2).
         */
        template<typename T1, typename T2>
        struct container_format<std::pair<T1,T2>>
        {
            const container_format_values mFormat;
            container_format() : mFormat({ '(', ')', ',' }) { }
        };
        
        // std::set
        
        template<typename T, typename Traits, typename Allocator>
        struct supported_container<std::set<T, Traits, Allocator>> : public std::true_type {};
        
        /**
         @brief Default format for std::set is {el1,...,eln}.
         */
        template<typename T, typename Traits, typename Allocator>
        struct container_format<std::set<T, Traits, Allocator>>
        {
            const container_format_values mFormat;
            container_format() : mFormat({ '{', '}', ',' }) { }
        };
        
        // std::unordered_map
        
        template<typename TKey, typename TVal>
        struct supported_container<std::unordered_map<TKey,TVal>> : public std::true_type {};
        
        /**
         @brief Default format for std::unordered_map.
         */
        template<typename TKey, typename TVal>
        struct container_format<std::unordered_map<TKey,TVal>>
        {
            const container_format_values mFormat;
            container_format() : mFormat({ '{', '}', ',' }) { }
        };
        
        // std::vector
        
        template<typename T>
        struct supported_container<std::vector<T>> : public std::true_type {};
        
        /**
         @brief Default format for std::vector is <el1,...,eln>.
         */
        template<typename T>
        struct container_format<std::vector<T>>
        {
            const container_format_values mFormat;
            container_format() : mFormat({ '<', '>', ',' }) { }
        };
    } // end namespace utils.io
} // end namespace utils

#endif
