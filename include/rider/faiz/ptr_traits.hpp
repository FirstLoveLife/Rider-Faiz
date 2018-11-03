#ifndef PTR_TRAITS
#define PTR_TRAITS
#include "rider/faiz/cstddef.hpp"
#include "rider/faiz/type_traits.hpp"
#include "rider/faiz/utility.hpp"
namespace rider::faiz
{
    class undefined;

    template<typename T>
    struct get_first_arg
    {
        using type = undefined;
    };
    template<template<typename, typename...> class Template,
        typename T,
        typename... Types>
    struct get_first_arg<Template<T, Types...>>
    {
        using type = T;
    };

    template<typename T>
    using get_first_arg_t = typename get_first_arg<T>::type;

    // Given Template<T, ...> and U return Template<U, ...>, otherwise invalid.
    template<typename T, typename U>
    struct replace_first_arg
    {
    };

    template<template<typename, typename...> class Template,
        typename U,
        typename T,
        typename... Types>
    struct replace_first_arg<Template<T, Types...>, U>
    {
        using type = Template<U, Types...>;
    };

    template<typename T, typename U>
    using replace_first_arg_t = typename replace_first_arg<T, U>::type;

    template<typename T>
    using make_not_void =
        typename faiz::conditional<is_void<T>::value, undefined, T>::type;

    /**
     * @brief  Uniform interface to all pointer-like types
     * @ingroup pointer_abstractions
     */
    template<typename _Ptr>
    struct pointer_traits
    {
    private:
        template<typename T>
        using elementtype_aux = typename T::elementtype;

        template<typename T>
        using differencetype_aux = typename T::differencetype;

        template<typename T, typename U, typename = void>
        struct rebind_aux : replace_first_arg<T, U>
        {
        };

        template<typename T, typename U>
        struct rebind_aux<T, U, void_t<typename T::template rebind<U>>>
        {
            using type = typename T::template rebind<U>;
        };

    public:
        /// The pointer type.
        using pointer = _Ptr;

        /// The type pointed to.
        using elementtype =
            faiz::detected_or_t<get_first_arg_t<_Ptr>, elementtype_aux, _Ptr>;

        /// The type used to represent the difference between two pointers.
        using differencetype =
            faiz::detected_or_t<ptrdiff_t, differencetype_aux, _Ptr>;

        /// A pointer to a different type.
        template<typename U>
        using rebind = typename rebind_aux<_Ptr, U>::type;

        static _Ptr pointer_to(make_not_void<elementtype>& __e)
        {
            return _Ptr::pointer_to(__e);
        }

        static_assert(!is_same<elementtype, undefined>::value,
            "pointer type defines elementtype or is like SomePointer<T, "
            "Args>");
    };

    /**
     * @brief  Partial specialization for built-in pointers.
     * @ingroup pointer_abstractions
     */
    template<typename T>
    struct pointer_traits<T*>
    {
        /// The pointer type
        using pointer = T*;
        /// The type pointed to
        using elementtype = T;
        /// Type used to represent the difference between two pointers
        using differencetype = ptrdiff_t;

        template<typename U>
        using rebind = U*;

        /**
         *  @brief  Obtain a pointer to an object
         *  @param  r  A reference to an object of type @c elementtype
         *  @return @c addressof(r)
         */
        static pointer pointer_to(make_not_void<elementtype>& r) noexcept
        {
            return faiz::addressof(r);
        }
    };


    template<typename Ptr>
    constexpr decltype(auto) to_address_aux(const Ptr& ptr) noexcept
    {
        return faiz::pointer_traits<Ptr>::to_address(ptr);
    }

    template<typename Ptr, typename... None>
    constexpr auto to_address_aux(const Ptr& ptr, None...) noexcept
    {
        return faiz::to_address_aux(ptr.operator->());
    }

    template<typename Tp>
    constexpr Tp* to_address(Tp* ptr) noexcept
    {
        return faiz::to_address_aux(ptr);
    }

    template<typename Ptr>
    constexpr auto to_address(const Ptr& ptr) noexcept
    {
        return faiz::to_address_aux(ptr);
    }

} // namespace rider::faiz
#endif