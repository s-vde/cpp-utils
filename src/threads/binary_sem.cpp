
#include "binary_sem.hpp"

namespace utils
{
    namespace threads
    {
        BinarySem::BinarySem(const id_t& id, const bool val)
        : mId(id)
        , mVal(val)
        , mMutex()
        , mCond() { }
        
        void BinarySem::wait()
        {
            // >>>>> mMutex
            std::unique_lock<std::mutex> ul(mMutex);
            // cond WAIT mCond
            mCond.wait(ul, [this] () { return mVal; } );
            mVal = false;
        }
        
        bool BinarySem::post(const bool val, const BroadcastMode& mode)
        {
            // >>>>> mMutex
            std::lock_guard<std::mutex> guard(mMutex);
            mVal = val;
            if (mode == BroadcastMode::NOTIFY_ONE)      { mCond.notify_one(); }
            else if (mode == BroadcastMode::NOTIFY_ALL) { mCond.notify_all(); }
            return true;
        }
    } // end namespace utils.threads
} // end namespace utils

