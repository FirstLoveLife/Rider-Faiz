/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Morwenn
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "rider/faiz/compressed_pair.hpp"
#include <catch2/catch.hpp>
#include <memory>
#include <utility>

namespace
{
	struct Base
	{
		virtual ~Base()
		{}
	};

	struct Derived : Base
	{};
} // namespace

TEST_CASE("assign rv pair U V")
{
	using Rider::Faiz::get;

	using P1 = Rider::Faiz::tight_pair<std::unique_ptr<Derived>, short>;
	using P2 = Rider::Faiz::tight_pair<std::unique_ptr<Base>, long>;
	P1 p1(std::unique_ptr<Derived>(), static_cast<short>(4));
	P2 p2;
	p2 = std::move(p1);
	CHECK(get<0>(p2) == nullptr);
	CHECK(get<1>(p2) == 4);
}
