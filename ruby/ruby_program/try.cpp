#include <iostream>

class father
{
	public:
		bool greet()
		{
			std::cout << "father" << std::endl;
		}

		bool call()
		{
			this->greet();
		}
};

class child : public father
{
	public:
		bool greet()
		{
			std::cout << "child" << std::endl;
		}
};

int main()
{
	child a;
	a.call();
	return 0;
}
