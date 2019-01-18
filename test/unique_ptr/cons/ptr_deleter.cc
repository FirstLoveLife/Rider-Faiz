// { dg-do run { target c++11 } }

// Copyright (C) 2010-2018 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// 20.9.10 Template class unique_ptr [unique.ptr]

#include "rider/faiz/unique_ptr.hpp"
#include <catch2/catch.hpp>
#include <memory>

namespace
{
	static int count;

	void
	del(int* p)
	{
		++count;
		delete p;
	}
	void
	vdel(int* p)
	{
		++count;
		delete[] p;
	}
} // namespace

TEST_CASE("ptr_deleter")
{
	{
		count = 0;
		{
			Rider::Faiz::unique_ptr<int, void (*)(int*)> p(nullptr, del);
		}
		CHECK(count == 0);
		{
			Rider::Faiz::unique_ptr<int, void (*)(int*)> p(new int, del);
		}
		CHECK(count == 1);
	}
	{
		count = 0;
		{
			Rider::Faiz::unique_ptr<int[], void (*)(int*)> p(nullptr, vdel);
		}
		CHECK(count == 0);
		{
			Rider::Faiz::unique_ptr<int[], void (*)(int*)> p(new int[1], vdel);
		}
		CHECK(count == 1);
	}
}
