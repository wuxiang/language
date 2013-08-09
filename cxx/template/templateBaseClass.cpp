#include <iostream>

//***********************first situation##############################
template<typename T>
class base
{
	public:
		base(const T& v): a(v)
		{
		}

		virtual ~base()
		{
		}

		virtual T getValue()
		{
			return a;
		}

		virtual T value()
		{
			return a;
		}

	private:
		T a;
};

class driver: public base<int>
{
	public:
		driver(const int a): base<int>(a), my(a)
		{
		}

		virtual int getValue()
		{
			return my * 10;
		}

	private:
		int my;
};

template<typename T>
class dr: public base<T>
{
	public:
		dr(const T& v): base<T>(v), mem(v)
		{
		}

		virtual T getValue()
		{
			return mem * 10;
		}

	private:
		T   mem;
};

//*************************************second situation########################
//class fun
//{
//	public:
//		template<typename T>
//		virtual  T  test(const T& t)
//		{
//			return t;
//		}
//};

int main()
{
	dr<int>  a(8);
	base<int>&  ref =  a;
	std::cout << ref.value() << std::endl;
	std::cout << ref.getValue() << std::endl;
	return 0;
}
