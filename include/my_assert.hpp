#include <iostream>


#define assert_m(expr, message)  \
    (!(expr)) ? \
        (my::__print_assert_msg("Assertion '", #expr, "' failed:\n",    \
                                    "file: '", __FILE__, "', line: ", __LINE__, ", function: '", __FUNCTION__, "'\n",   \
                                    #message""), \
        abort())   \
    : (void)0

namespace my
{
    template<typename ... Args>
    inline void __print_assert_msg(Args&& ... args) noexcept
    {
        (std::cerr << ... << args) << "\n";
    }
}