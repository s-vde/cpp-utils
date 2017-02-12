
#ifndef ALGO_HPP_INCLUDED
#define ALGO_HPP_INCLUDED

#include <algorithm>    // std::find_if, std::transform

/*---------------------------------------------------------------------------75*/
/**
 @file algo.hpp
 @brief Definition of function templates extending the algorithms from 
 <algorithm>.
 @author Susanne van den Elsen
 @date 2015-2016
 */
/*---------------------------------------------------------------------------++*/

namespace utils
{
    namespace algo
    {
        /**
         @brief Finds the first element in the range [first,last) satisfying 
         the given binary predicate on the element's index and value. Returns 
         last if no such element exists.
         @details Sets up an index variable, initialized with 0, and calls 
         std::find_if with a unary predicate wrapping the given binary 
         predicate, providing it access to the index variable and updating 
         the index variable at the end of each iteration.
         @see http://www.cplusplus.com/reference/algorithm/find_if/
         */
        template<typename InputIterator, typename BinaryPredicate>
        InputIterator find_if_with_index(
            InputIterator first,
            InputIterator last,
            BinaryPredicate pred)
        {
            unsigned int index = 0;
            return
                std::find_if(
                    first, last,
                    [&pred, &index] (const auto& el) {
                        bool res = pred(index, el);
                        ++index;
                        return res;
                    }
                );
        }
        
        /**
         @brief Applies the given unary operation sequentially to elements in 
         the range [first,last) that satisfy the given unary predicate and 
         stores the result in the range that begins at result.
         @note When transforming one ordered structure into another,
         el1 <= el2 does not imply unary_op(e1) <= unary_op(e2).
         @see http://www.cplusplus.com/reference/algorithm/transform/
         */
        template<
            typename InputIterator,
            typename OutputIterator,
            typename UnaryPredicate,
            typename UnaryOperation
        >
        OutputIterator transform_if(
            InputIterator first,
            InputIterator last,
            OutputIterator result,
            UnaryPredicate pred,
            UnaryOperation unary_op)
        {
            while (first != last) {
                if (pred(*first)) { *result++ = unary_op(*first); }
                ++first;
            }
            return result;
        }
       
       template <typename InputIt, typename OutputIt, typename UnaryPredicate, typename index_t>
       void copy_index_if(InputIt&& input_begin,
                          InputIt&& input_end,
                          OutputIt&& output,
                          UnaryPredicate&& predicate,
                          index_t&& index=index_t{})
       {
          while (input_begin != input_end)
          {
             if (predicate(*input_begin))
             {
                *output++ = index++;
             }
             ++input_begin;
          }
       }
    } // end namespace utils.algo
} // end namespace utils

#endif
