#include <iostream>
#include <iterator>
//using namespace std;

int main()
{
	double value1, value2;
	std::cout << "Please, insert two values: ";

	std::istream_iterator<double> eos;         // end-of-stream iterator
	std::istream_iterator<double> iit (std::cin);   // stdin iterator

	if (iit!=eos) value1=*iit;

	iit++;
	if (iit!=eos) value2=*iit;

	std::cout << value1 << "*" << value2 << "=" << (value1*value2) << std::endl;
	return 0;
}
