//#include <algorithm>
//#include <iterator>

extern "C"
{
  struct ctor_type
  {
    typedef void(*function_type)();
//    typedef std::reverse_iterator<const function_type*> const_reverse_iterator;
  };

  extern ctor_type::function_type _ctors_end[];
  extern ctor_type::function_type _ctors_begin[];
  extern ctor_type::function_type __init_array_start[];
  extern ctor_type::function_type __init_array_end[];
}

namespace crt
{
  void init_ctors();
}

void crt::init_ctors()
{
    auto array = _ctors_begin;
    while (array < _ctors_end)
    {
        (*array)();
        array++;
    }

    array = __init_array_start;
    while (array < __init_array_end)
    {
        (*array)();
        array++;
    }
//  std::for_each(ctor_type::const_reverse_iterator(_ctors_end),
//                ctor_type::const_reverse_iterator(_ctors_begin),
//                [](const ctor_type::function_type pf)
//                {
//                  pf();
//                });
}
