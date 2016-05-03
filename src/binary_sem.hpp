
#ifndef BINARY_SEM_HPP_INCLUDED
#define BINARY_SEM_HPP_INCLUDED

#include <thread>

/*---------------------------------------------------------------------------75*/
/**
 @file binary_sem.hpp
 @brief Definition of class BinarySem.
 @author Susanne van den Elsen
 @date 2015
 */
/*---------------------------------------------------------------------------++*/

namespace utils
{
    namespace threads
    {
        /**
         @brief BinarySem implements a semaphore whose value is restricted 
         to be boolean (i.e. resource is either taken or available).
         @details It encapsulates a mutex-protected boolean variable (mVar) 
         and a condition variable (mCond) and provides waiting functionality 
         and three types of broadcasting:
         - NOTIFY_ONE:    unblocks *>= 1* threads blocked on mCond (if any);
         - NOTIFY_ALL:    unblocks *all* threads blocked on mCond;
         - PRIVATE:       no broadcasting.
         */
        class BinarySem
        {
        public:
            
            enum class BroadcastMode { PRIVATE, NOTIFY_ONE, NOTIFY_ALL };
            using id_t = int;
            
            // CTORS / DTOR
            
            explicit BinarySem(const id_t&, const bool val=false);
            
            BinarySem(const BinarySem&) = delete;
            BinarySem(BinarySem&&) = delete;
            ~BinarySem() = default;
			
			// OPERATORS
			
            BinarySem& operator=(const BinarySem&) = delete;
            BinarySem& operator=(BinarySem&&) = delete;
            
            //

            /**
             @brief Wait on mCond until mVal is true and then set mVal back 
             to false.
             */
            void wait();

            /**
             @brief Sets mVal is to val and broadcasts mCond according to
             the provided BroadcastMode.
             */
            bool post(
                const bool val,
                const BroadcastMode& mode=BroadcastMode::PRIVATE
            );
            
        private:
            
            id_t mId;

            /// @brief The boolean variable of the semaphore.
            bool mVal;
			
            /// @brief The mutex protecting mVal and mCond.
            std::mutex mMutex;
			
            /// @brief The condition variable to conditionally wait on.
            std::condition_variable mCond;
            
        }; // end class BinarySem
    } // end namespace utils.threads
} // end namespace utils

#endif
