#pragma once

#include <type_traits>

template< typename T, typename Ret, typename ...Args>
struct is_right_callable
{
    /* SFINAE operator-has-correct-sig :) */
    template<typename A>
    static std::true_type test(Ret(A::*)(Args...)const) {
        return std::true_type();
    }

    /* SFINAE operator-exists :) */
    template <typename A>
    static decltype(test(&A::operator()))
        test(decltype(&A::operator()), void*) {
        /* Operator exists. What about sig? */
        typedef decltype(test(&A::operator())) return_type;
        return return_type();
    }

    /* SFINAE game over :( */
    template<typename A>
    static std::false_type test(...) {
        return std::false_type();
    }

    /* This will be either `std::true_type` or `std::false_type` */
    typedef decltype(test<T>(0, 0)) type;

    static const bool value = type::value; /* Which is it? */
};

template<typename Ret, typename ...Args>
struct is_right_callable<Ret(*)(Args...), Ret, Args...>
{
    static const bool value = true;

};
