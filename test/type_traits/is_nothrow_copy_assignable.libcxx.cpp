//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// type_traits

// is_nothrow_copy_assignable

// #include "../test_macros.h"
#include "test-utilities.hpp"
#include <catch2/catch.hpp>

#include "rider/faiz/type_traits.hpp"

namespace
{

	template<class T>
	void
	test_has_nothrow_assign()
	{
		STATIC_REQUIRE(Rider::Faiz::is_nothrow_copy_assignable<T>::value);
		STATIC_REQUIRE(Rider::Faiz::is_nothrow_copy_assignable_v<T>);
	}

	template<class T>
	void
	test_has_not_nothrow_assign()
	{
		STATIC_REQUIRE(!Rider::Faiz::is_nothrow_copy_assignable<T>::value);
		STATIC_REQUIRE(!Rider::Faiz::is_nothrow_copy_assignable_v<T>);
	}

	class Empty
	{};

	struct NotEmpty
	{
		virtual ~NotEmpty();
	};

	union Union
	{};

	struct bit_zero
	{
		int : 0;
	};

	struct A
	{
		A&
		operator=(const A&);
	};

} // namespace
TEST_CASE("is_nothrow_copy_assignable.libcxx: ")
{
	test_has_nothrow_assign<int&>();
	test_has_nothrow_assign<Union>();
	test_has_nothrow_assign<Empty>();
	test_has_nothrow_assign<int>();
	test_has_nothrow_assign<double>();
	test_has_nothrow_assign<int*>();
	test_has_nothrow_assign<const int*>();
	test_has_nothrow_assign<NotEmpty>();
	test_has_nothrow_assign<bit_zero>();

	test_has_not_nothrow_assign<const int>();
	test_has_not_nothrow_assign<void>();
	test_has_not_nothrow_assign<A>();
}
