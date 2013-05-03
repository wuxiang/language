/*********************************************
 * 1,static member in base class can be inherited by father class
 *   and they point to the same variable
 * ******************************************/
#include <iostream>

class Base
{
	public:
		static int  m_static;

		// child class's virtual can use variable which is define only in child class
		virtual void func()
		{
			std::cout << "hello" << std::endl;
		}

		void usestatic()
		{
			std::cout << m_static << std::endl;
		}

};

int Base::m_static = 0;

class Inheri: public Base
{
	public:
		static int m_static;
		static int m_static_child;

		Inheri()
		{
			m_my = 88888888;
		}
		virtual void func()
		{
			std::cout << m_my << std::endl;
		}

		void usestaticIn()
		{
			std::cout << m_static << std::endl;
		}

	private:
		int   m_my;
};
//int Inheri::m_static = 0; redefinition
int Inheri::m_static = 0;
int Inheri::m_static_child = 0;

int main()
{
	Base::m_static = 9;
	std::cout << Base::m_static << std::endl;
	std::cout << Inheri::m_static << std::endl;

	Inheri::m_static = 8;
	std::cout << Base::m_static << std::endl;
	std::cout << Inheri::m_static << std::endl;

	Base  varB;
	Inheri  varIn;
	Base&  bs = varIn;
	bs.func();

	varB.usestatic();
	varIn.usestaticIn();
	return 0;
}
