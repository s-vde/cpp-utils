
#pragma once

#include <assert.h>
#include <set>
#include <unordered_map>
#include "algo.hpp"

/*---------------------------------------------------------------------------75*/
/**
 @file map_utils.hpp
 @brief Definitions of utility function templates for std::unordered_map.
 @author Susanne van den Elsen
 @date 2015
 */
/*---------------------------------------------------------------------------++*/

namespace utils
{
    namespace maps
    {		
		/**
		 @brief Applies the given binary operation to pairs of values in M1
		 and M2 that share the same key. Stores the results in a new 
		 unordered_map under the shared key.
		 */
        template<typename KeyT, typename ValT1, typename ValT2, typename BinaryOperation>
		std::unordered_map<KeyT,typename BinaryOperation::result_type> zip(
            std::unordered_map<KeyT,ValT1>& M1,
            std::unordered_map<KeyT,ValT2>& M2,
            BinaryOperation binary_op)
        {
            using ZipMap = std::unordered_map<KeyT,typename BinaryOperation::result_type>;
            ZipMap M{};
            for (const auto& mapping1 : M1)
            {
                auto mapping2 = M2.find(mapping1.first);
                /// @pre keys(M1) is subset of keys(M2)
                assert(mapping2 != M2.end());
                M.insert(typename ZipMap::value_type(
                    mapping1.first,
                    binary_op(mapping1.second, mapping2->second))
                );
            }
            return M;
        }
    } // end namespace utils.maps
} // end namespace utils
