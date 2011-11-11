
template<typename T>
const T&  s_max(const T& a, const T& b)
{
	return (a > b ? a : b);
}

template<typename T1, typename T2>
const T2 s_max(const T1& a, const T2& b)
{
	return (a > b ? a : b);
}

