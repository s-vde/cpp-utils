#pragma once

#include "algo.hpp"

#include <assert.h>
#include <unordered_map>

//--------------------------------------------------------------------------------------------------
/// @file zip_map_values.hpp
/// @brief Zips the values mapped to by the same keys in two unordered_maps
/// @author Susanne van den Elsen
/// @date 2015-2017
//--------------------------------------------------------------------------------------------------


namespace utils {
namespace algorithm {

/// @brief Applies the given zip_function to pairs of values in map1 and map2 that share the
/// same key. Stores the results in a new unordered_map under the shared key. Assumes that the
/// keys of map2 are a subset of the keys of map1.

template <typename KeyType, typename ValueType1, typename ValueType2, typename ZipType>
std::unordered_map<KeyType, ZipType> zip_map_values(
   const std::unordered_map<KeyType, ValueType1>& map1,
   const std::unordered_map<KeyType, ValueType2>& map2,
   const std::function<ZipType(const ValueType1&, const ValueType2&)>& zip_function)
{
   using ZippedMap = std::unordered_map<KeyType, ZipType>;
   ZippedMap zipped;
   std::transform(map1.begin(), map1.end(), std::inserter(zipped, zipped.end()),
                  [&map2, &zip_function](const auto& mapping1) {
                     const auto mapping2 = map2.find(mapping1.first);
                     if (mapping2 == map2.end())
                        throw std::invalid_argument("keys(map2) should be a subset of keys(map1)");
                     return typename ZippedMap::value_type(
                        mapping1.first, zip_function(mapping1.second, mapping2->second));
                  });
   return zipped;
}
}
}   // end namespace utils.algorithm
