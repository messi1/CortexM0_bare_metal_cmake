#pragma once

  // Taken (with slight modification) from boost::noncopyable.

namespace util
{
   class noncopyable
   {
      protected:
        noncopyable() = default;
        ~noncopyable() = default;

      private:
        noncopyable(const noncopyable&) = delete;
        noncopyable& operator=(const noncopyable&) = delete;
   };
}

