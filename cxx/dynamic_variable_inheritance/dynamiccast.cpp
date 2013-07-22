#include <iostream>

class Base
{
	public:
		Base()
		{
			std::cout << __FUNCTION__ << std::endl;
		}

		virtual ~Base()
		{
		}
};

class Inheri: public Base
{
	public:
		Inheri()
		{
			std::cout << __FUNCTION__ << std::endl;
		}
};

class TInheri: public Inheri
{
	public:
		TInheri(const std::string& str): value(str)
		{
			std::cout << __FUNCTION__ << std::endl;
		}

		void sayHi()
		{
			std::cout << "hello " << value << std::endl;
		}

	private:
		std::string  value;
};

int main()
{
	Base* pBase = new Inheri();
	Inheri* pIn = dynamic_cast<Inheri*>(pBase);
	if (!pIn)
	{
		std::cout << "exception in Inheri" << std::endl;
	}

	Base* pSec = new TInheri("kakaxi");
	TInheri* pT = dynamic_cast<TInheri*>(pSec);
	if (!pT)
	{
		std::cout << "exception in TInheri" << std::endl;
	}
	pT->sayHi();

	return 0;
}
