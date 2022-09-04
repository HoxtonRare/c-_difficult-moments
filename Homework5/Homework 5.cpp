#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_set>
#include "Windows.h"

using namespace std;

//task 1

template <class Iter>
void sortWord(Iter begin, Iter end)
{
	unordered_set<string> unique;
	copy(begin, end, inserter(unique, unique.begin()));
	for (const auto& w : unique)
	{
		cout << w << "\t";
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);
	//task 1
	cout << "\t\t TASK 1: " << endl;

	vector<string> word = {"Hello", "Goodbye", "Hello", "Thanks", "invisible", "invisible", "Nice"};
	sortWord(word.begin(), word.end());

	//task 2
	cout << "\t\t TASK 2: " << endl;

	string text;
	string separators = ".!?";
	string temp;
	cout << "Введите предложения для считывания( Не забывайте ставить знаки препинания в конце предложений. ): " << endl;
	getline(cin, text);
	multimap<size_t, string> split;
	for (auto iter = text.begin(); iter != text.end(); iter++)
	{
		auto sign = find_first_of(iter, text.end(), separators.begin(), separators.end());
		if (sign != text.end())
		{
			auto sentBegin = distance(text.begin(), iter);
			auto sentEnd = distance(text.begin(), sign);
			temp = text.substr(sentBegin, sentEnd - sentBegin + 1);
			iter = sign;
			if (temp[0] == ' ')
			{
				temp = temp.substr(1);
			}
			split.emplace(temp.size(), temp);
		}
	}
	cout << endl << "Отсортированные по длине предложения: " << endl;
	for (const auto& n : split)
	{
		cout << n.second << endl;
	}
	return 0;
}