// Range v3 library
//
//  Copyright Eric Niebler 2013-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//
#ifndef STATIC_CONST
#define STATIC_CONST

#include "rider/faiz/faiz_fwd.hpp"
#include "rider/faiz/macros.hpp"
namespace Rider::Faiz
{

	Tpl<Typ T> struct static_const
	{
		static cexp T value{};
	};

	Tpl<Typ T> cexp T static_const<T>::value;
} // namespace Rider::Faiz

#endif
