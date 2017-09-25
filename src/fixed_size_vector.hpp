#pragma once

// UTILS
#include "container_io.hpp"

// STL
#include <vector>

//--------------------------------------------------------------------------------------90
/// @file fixed_size_vector.hpp
/// @author Susanne van den Elsen
/// @date 2016
//----------------------------------------------------------------------------------------

namespace datastructures
{
   //-------------------------------------------------------------------------------------
   
   // forward declarations
   
   template <typename T>
   class fixed_size_vector;
   
   template <typename T>
   std::ostream& operator <<(std::ostream& os, const fixed_size_vector<T>& vector);
   
   //-------------------------------------------------------------------------------------
   
   template <typename T>
   class fixed_size_vector
   {
   public:
      
      using value_t = T;
      
      using vector_t = std::vector<value_t>;
      
      /// @brief Constructor
      
      explicit fixed_size_vector(std::size_t size, const value_t& value=value_t())
      : m_vector(size, value)
      , m_size(size)
      {
      }
      
      /// @brief Read-only subscript operator.
      
      const value_t& operator[](int index) const
      {
         return m_vector[index];
      }
      
      /// @brief Subscript operator.
      
      value_t& operator[](int index)
      {
         return m_vector[index];
      }
      
      /// @brief Returns the (constant) size of this fixed-size vector.
      
      std::size_t size() const
      {
         return m_size;
      }
      
      typename vector_t::iterator begin()
      {
          return m_vector.begin();
      }
      
      typename vector_t::const_iterator cbegin() const
      {
         return m_vector.cbegin();
      }
      
      typename vector_t::iterator end()
      {
          return m_vector.end();
      }
      
      
      typename vector_t::const_iterator cend() const
      {
         return m_vector.cend();
      }
      
   private:
      
      vector_t m_vector;
      
      std::size_t m_size;
      
      friend std::ostream& operator << <>(std::ostream&, const fixed_size_vector<T>&);
      
   }; // end class template fixed_size_vector
   
   //-------------------------------------------------------------------------------------
   
   template <typename T>
   std::ostream& operator << (std::ostream& os, const fixed_size_vector<T>& vector)
   {
      os << vector.m_vector;
      return os;
   }
   
   //-------------------------------------------------------------------------------------
   
} // end namespace datastructures
