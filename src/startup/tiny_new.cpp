#include <cstddef>

//#include <new>
//#include <malloc.h>

// void *operator new(std::size_t size); // replaceable, nodiscard in C++2a
// void *operator new(
//    std::size_t size,
//    std::align_val_t alignment); // replaceable, C++17, nodiscard in C++2a
// void *operator new(
//    std::size_t size,
//    const std::nothrow_t &) noexcept; // replaceable, nodiscard in C++2a
// void *operator new(std::size_t size, std::align_val_t alignment,
//                   const std::nothrow_t &) noexcept;
/* Optionally you can override the 'nothrow' versions as well.
   This is useful if you want to catch failed allocs with your
   own debug code, or keep track of heap usage for example,
   rather than just eliminate exceptions.
 */

extern "C" void __cxa_pure_virtual()
{
    while (1)
        ;
}

namespace std {
struct nothrow_t
{
    //
    explicit nothrow_t() = default;
};
enum class align_val_t : std::size_t
{
};
} // namespace std

[[nodiscard]] void* operator new(std::size_t /*size*/)
{
    //
    return reinterpret_cast<void*>(0x48000000) /*malloc(size)*/;
}

[[nodiscard]] void* operator new(std::size_t, void* p) noexcept
{
    //
    return p;
}

[[nodiscard]] void* operator new(std::size_t /*size*/, std::align_val_t /*alignment*/,
                                 const std::nothrow_t&) noexcept
{
    //
    return reinterpret_cast<void*>(0x48000000);
}

[[nodiscard]] void* operator new(std::size_t /*size*/, const std::nothrow_t& /*nothrow_value*/) noexcept
{
    //
    return reinterpret_cast<void*>(0x48000000) /*malloc(size)*/;
}

void* operator new[](std::size_t /*size*/, const std::nothrow_t&) noexcept
{
    //
    return reinterpret_cast<void*>(0x48000000) /*malloc(size)*/;
}

void operator delete(void* /*ptr*/)
{
    //
    /*free(ptr);*/
}

void operator delete(void* /*ptr*/, unsigned int)
{
    //
    /*free(ptr);*/
}

void operator delete(void* /*ptr*/, const std::nothrow_t&)
{
    //
    /*free(ptr);*/
}

void operator delete[](void* /*ptr*/)
{
    //
    /*free(ptr);*/
}

void operator delete[](void* /*ptr*/, unsigned int)
{
    //
    /*free(ptr);*/
}

void operator delete[](void* /*ptr*/, const std::nothrow_t&)
{
    //
    /*free(ptr);*/
}

// eof
