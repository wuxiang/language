#include <iostream>

class base
{
	public:
		base(int a)
		{
			std::cout << "base::base(a)" << std::endl;
		}
};

int main()
{
	base* pSingle = new base(10);
	base* pBase = new base[5]; /*error happen*/
	return 0;
}
