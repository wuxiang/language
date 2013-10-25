#include <iostream>

class base
{
	public:
		base()
		{
		}

		base(int v1, int v2): a(v1), b(v2)
		{
		}

		base& operator=(const base& bs)
		{
			a = bs.a;
			b = bs.b;
			return *this;
		}
	protected:
		int a;
		int b;
};

class driver: public base
{
	public:
		driver()
		{
		}

		driver( int a ,int b, int v): base(a, b)
		{
			c = v;
		}

		driver& operator=(const driver& rv)
		{
			c = rv.c;
			base::operator=(rv);
			return *this;
		}

		void print()
		{
			std::cout << "a = " << a << std::endl;
			std::cout << "b = " << b << std::endl;
			std::cout << "c = " << c << std::endl;
		}

	private:
		int c;
};

int main()
{
	driver  a;
	a.print();
	std::cout << "============" << std::endl;
	driver  b(8, 88, 19);
	b.print();
	std::cout << "============" << std::endl;
	a = b;
	a.print();
	std::cout << "============" << std::endl;
	return 0;
}
