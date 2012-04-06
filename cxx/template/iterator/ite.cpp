#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
//using namespace std;

int main()
{
	std::vector<std::string> ctr;
	std::copy(std::istream_iterator<std::string>(std::cin), 
				std::istream_iterator<std::string>(), 
				std::back_inserter(ctr));

	std::sort(ctr.begin(), ctr.end());
	std::unique_copy(ctr.begin(), ctr.end(), 
				std::ostream_iterator<std::string>(std::cout,"\n"));
	return 0;
}
