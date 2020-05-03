//#include <algorithm>
//#include <iterator>


struct ctor_type {
    using function_ptr = auto (*)() -> void;
};

//  extern ctor_type::function_type _ctors_end[];
//  extern ctor_type::function_type _ctors_begin[];
extern ctor_type::function_ptr __init_array_start[];
extern ctor_type::function_ptr __init_array_end[];
extern ctor_type::function_ptr __preinit_array_start[];
extern ctor_type::function_ptr __preinit_array_end[];
extern ctor_type::function_ptr __fini_array_start[];
extern ctor_type::function_ptr __fini_array_end[];


namespace crt {
    void init_ctors();
    void init_dtors();
} // namespace crt

void crt::init_ctors() {
    //    auto array = _ctors_begin;
    //    while( array < _ctors_end )
    //    {
    //        (*array)();
    //        array++;
    //    }

    int size = __preinit_array_end - __preinit_array_start;
    for (int i = 0; i < size; i++)
    __preinit_array_start[i]();

    size = __init_array_end - __init_array_start;
    for (int i = 0; i < size; i++)
    __init_array_start[i]();

    //    array = __init_array_start;
    //    while( array < __init_array_end )
    //    {
    //        (*array)();
    //        array++;
    //    }
}

void crt::init_dtors()
{
    int size = __fini_array_end - __fini_array_start;
    for (int i = 0; i < size; i++)
    __fini_array_start[i]();

    //    auto array = __fini_array_start;
    //    while( array < __fini_array_end )
    //    {
    //        (*array)();
    //        array++;
    //    }
}
