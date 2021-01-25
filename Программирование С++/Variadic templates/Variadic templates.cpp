/*
							Шаблоны функций с переменным числом параметров

	12.	Написать функцию с FMaxMin с переменным числом аргументов различного типа, которая вычисляет максимум среди аргументов,
	имеющих тип числа с плавающей запятой, и минимум среди аргументов целого типа 
	(int, short, char, long, long long и т.д., знаковые и беззнаковые, с const и без). Например, результатом выполнения 
	FMaxMin(3, 2, 3.5, 4, 32.7, ‘a’, string(“abc”) ) будет пара ( 32.7, 2).

*/

#include <iostream>
#include <algorithm>
#include <type_traits>

using namespace std;


template <bool b, typename T, typename ... Args> struct Select;

template<typename T, typename ... Args>
struct Select<true, T, Args...>
{
	static auto delete_not_int(T x, Args...args);
	static auto delete_not_float(T x, Args...args);

};

template<typename T, typename ... Args>
struct Select<false, T, Args...>
{
	static auto delete_not_int(T x, Args...args);
	static auto delete_not_float(T x, Args...args);
};

//сравниваем два элементаа
template <bool b, typename T, typename U> struct my_comparisson;

template <typename T, typename U>
struct my_comparisson <true, T, U>
{
	static auto get_max(T x, U y)
	{
		return (x < y) ? y : x;
	}
	static auto get_min(T x, U y)
	{
		return (x < y) ? x : y;
	}
};

template <typename T, typename U>
struct my_comparisson <false, T, U>
{
	static auto get_max(T x, U y)
	{
		return x;
	}
	static auto get_min(T x, U y)
	{
		return x;
	}
};

//находим int 
template <typename ... Args> struct GetNumberOfIntegerArguments;

template <typename T,typename ... Args>
struct GetNumberOfIntegerArguments<T, Args...>
{
	static constexpr int value = (is_integral<T>::value ? 1 : 0) + GetNumberOfIntegerArguments<Args...>::value;
};

template<typename T>
struct GetNumberOfIntegerArguments<T>
{
	static constexpr int value= is_integral<T>::value ? 1 : 0;
};

//находим double 
template <typename ... Args> struct GetNumberOfFloatArguments;

template <typename T, typename ... Args>
struct GetNumberOfFloatArguments<T, Args...>
{
	static constexpr int value = (is_floating_point<T>::value ? 1 : 0) + GetNumberOfFloatArguments<Args...>::value;
};

template<typename T>
struct GetNumberOfFloatArguments<T>
{
	static constexpr int value = is_floating_point<T>::value ? 1 : 0;
};

template<typename T, typename... Args>
auto FMin(T x, Args... args)
{
	static_assert(GetNumberOfIntegerArguments<T, Args...>::value != 0, "No integral arguments");
	return Select<is_integral<T>::value, T, Args...>::delete_not_int(x, args...);
}

template<typename T, typename... Args>
auto FMax(T x, Args... args)
{
	static_assert(GetNumberOfFloatArguments<T, Args...>::value != 0, "No float arguments");
	return Select<is_floating_point<T>::value, T, Args...>::delete_not_float(x, args...);
}

template<typename T, typename... Args>
std::pair<double,int> FMaxMin(T x, Args... args)
{
	double fst = FMax(x, args...);
	int snd = FMin(x, args...);
	return make_pair(fst, snd);
}

template<typename T>
auto FindMinInteger(T xmin)
{
	return xmin;
}

template<typename T, typename U, typename... Args>
auto FindMinInteger(T xmin, U x, Args...args)
{
	return FindMinInteger(my_comparisson<is_integral<U>::value, T, U>::get_min(xmin, x), args...);
}

template <typename T, typename ... Args>
auto Select<true, T, Args...>::delete_not_int(T x, Args...args)
{
	return FindMinInteger(x, args...);
}

template <typename T, typename ... Args>
auto Select<false, T, Args...>::delete_not_int(T x, Args...args) 
{
	return FMin(args...);
}

template<typename T>
auto FindMaxFloat(T xmax)
{
	return xmax;
}

template<typename T, typename U, typename... Args>
auto FindMaxFloat(T xmax, U x, Args...args)
{
	return FindMaxFloat(my_comparisson<is_floating_point<U>::value, T, U>::get_max(xmax, x), args...);
}

template <typename T, typename ... Args>
auto Select<true, T, Args...>::delete_not_float(T x, Args...args)
{
	return FindMaxFloat(x, args...);
}

template <typename T, typename ... Args>
auto Select<false, T, Args...>::delete_not_float(T x, Args...args)
{
	return FMax(args...);
}

int main()
{
	FMaxMin(12, 3.4,-4);
	return 0;
}
