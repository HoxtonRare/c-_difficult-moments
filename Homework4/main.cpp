#include <iostream>
#include <vector>
#include <algorithm>
#include <clocale>
#include <cmath>
#include <numeric>

using namespace std;

template <class Container, class T>
void insert_sorted(Container& v, const T& value)
{
	typename Container::iterator iter = upper_bound(begin(v), end(v), value);
	v.insert(iter, value);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	//task1
	cout << "\t\tTASK 1: " << endl;

	vector<int> v = { 1,3,4,7 };
	insert_sorted(v, 6);
	for (auto it : v)
		cout << it << " ";
	cout << endl;
	vector<char> v1 = { 'a', 'c', 'e', 'g' };
	insert_sorted(v1, 'd');
	for (auto it : v1)
		cout << it << " ";
	cout << "\n\n";

	//task2
	cout << "\t\tTASK 2: " << endl;

	vector<double> vec(100);
	double analog = 0.0;
	generate(vec.begin(), vec.end(), [&analog](const double pi = atan(1.0) * 4)
		mutable {analog += (2 * pi / 100); return (32 * sin(analog) + 100); });
	cout << "Аналоговый сигнал:" << endl;

	copy(vec.begin(), vec.end(), ostream_iterator<double>{cout, "\t"});
	cout << "\n\n";

	vector<double> v3;
	auto digit = [](double d) {return trunc(d); };
	transform(vec.begin(), vec.end(), back_inserter(v3), digit);
	cout << "Цифровой сигнал:" << endl;

	copy(v3.begin(), v3.end(), ostream_iterator<double>{cout, "\t"});

	cout << "\n\n";

	vector<double> e;
	transform(vec.begin(), vec.end(), v3.begin(), back_inserter(e), [](double i, double j)
		{return pow((i - j), 2); });
	cout << "Погрешности = " << accumulate(begin(e), end(e), decltype(e)::value_type(0.0)) << endl;
	return 0;
}