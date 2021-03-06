// { dg-do compile { target c++11 } }

// Copyright (C) 2008-2018 Free Software Foundation, Inc.
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

// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include <memory>

#include <catch2/catch.hpp>

struct base
{
	virtual ~base()
	{}
};
struct derived : base
{};

void
test01()
{
	Rider::Faiz::unique_ptr<derived> p1(new derived);
	Rider::Faiz::unique_ptr<derived> p2(new derived);
	//  p2 = p1;  // should not compile
	p2 = std::move(p1);
	Rider::Faiz::unique_ptr<base> p3(new base);
	//  p3 = p2;  // should not compile
	p3 = std::move(p2);
}

void
test02()
{
	Rider::Faiz::unique_ptr<int[]> p1(new int(420));
	Rider::Faiz::unique_ptr<int[]> p2 = p1; // { dg-error "deleted" }
}

void
test03()
{
	Rider::Faiz::unique_ptr<int[2]> p1(new int[3]); // { dg-error "no match" }
	Rider::Faiz::unique_ptr<int[2]> p2 = p1; // { dg-error "deleted" }
}

struct base_pointer
{
	operator base*() const
	{
		return nullptr;
	}
};

template<typename T>
struct deleter
{
	deleter() = default;
	template<typename U>
	deleter(const deleter<U>)
	{}
	typedef T pointer;
	void operator()(T) const
	{}
};

void
test04()
{
	// Disallow conversions from incompatible deleter
	Rider::Faiz::unique_ptr<derived[], deleter<base_pointer>> p;
	Rider::Faiz::unique_ptr<base[], deleter<base*>> upA;
	upA = std::move(p); // { dg-error "no match" }
}

// { dg-prune-output "include" }
