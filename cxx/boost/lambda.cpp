#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

template<typename _T>
class  plus
{
	public:
		_T  operator()(const _T& a, const _T& b)
		{
			return a + b;
		}
};

int main()
{
	std::vector<int>  vInt;
	for (int i = 0; i < 5; ++i)
	{
		vInt.push_back(i);
	}

	//std::transform(vInt.begin(), vInt.end(), std::ostream_iterator<int>(std::cout), std::bind(plus<int>(), 1, std::placeholders::_1));
	//std::transform(vInt.begin(), vInt.end(), std::ostream_iterator<int>(std::cout), 1 + _1);
	std::transform(vInt.begin(), vInt.end(), std::ostream_iterator<int>(std::cout), 1 + boost::lambda::_1);
	//std::transform(vInt.begin(), vInt.end(), std::ostream_iterator<int>(std::cout), boost::bind(plus<int>(), _1, 2));
	std::cout << "\n";

    std::vector<int> vec(5);
    std::for_each(vInt.begin(), vInt.end(), boost::lambda::_1 * 10 + 8);
    std::cout << "vec" << "\n";
    std::transform(vInt.begin(), vInt.end(), vec.end(), boost::lambda::_1 + 8);

    return 0;
}
