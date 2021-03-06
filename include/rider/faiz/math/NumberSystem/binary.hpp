#ifndef __BINARY_H_
#define __BINARY_H_
#include "rider/faiz/macros.hpp"

// namespace Rider::Faiz
// {
// 	Tpl<char high, char... digits> cfn
// 	operator"" _b()
// 	{
// 		static_assert(high == '0' or high == '1', "no binary number!");
// 		cIf(sizeof...(digits) == 0)
// 		{
// 			return high - '0';
// 		}
// 		cElse
// 		{
// 			return (high - '0') * (1 << sizeof...(digits))
// 				+ operator"" _b<digits...>();
// 		}
// 	}
// } // namespace Rider::Faiz

namespace Rider::Faiz
{
	namespace detail
	{
		Tpl<char Chs> cexp int
		toDecImpl()
		{
			return Chs > '9' ? Chs - 'A' + 10 : Chs - '0';
		}
	} // namespace detail
	Tpl<int from, char... Chs> cexp int
	toDec()
	{
		int ret{};

		return ((ret *= from, ret += detail::toDecImpl<Chs>()), ...);
	}
	inline namespace literals
	{
		Tpl<char... Chs> cexp int operator"" _B()
		{
			return toDec<2, Chs...>();
		}
		Tpl<char... Chs> cexp int operator"" _O()
		{
			return toDec<8, Chs...>();
		}

		// I decide not to provide heximal, too ugly

	} // namespace literals
} // namespace Rider::Faiz

#endif // __BINARY_H_
