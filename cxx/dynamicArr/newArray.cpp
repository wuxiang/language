#include <iostream>

class base
{
	public:
		base()
		{
			std::cout << "base::base()" << std::endl;
		}

		~base()
		{
			std::cout << "base::~base()" << std::endl;
		}
};

int main()
{
	base* ptr = new base[5];
	delete []ptr;
	return 0;
}
