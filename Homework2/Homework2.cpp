#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "Timer.h"

using namespace std;

template <typename T>
void Swap(T* ptr1, T* ptr2)
{
	T temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

template <typename T>
void SortPointers(vector <T*>& a)
{
	sort(a.begin(), a.end(), [](T* a, T* b) {return *a < *b; });
}

void sortGls(ifstream& book)
{
		Timer t;
		string vowels = "АУОИЭЫЯЮЕЁауоиэыяюеё";
		ifstream book1("voina-i-mir.txt");
		if (book1.is_open())
		{
			t.start("Способ 1");
			size_t count = count_if(istreambuf_iterator<char>(book1), istreambuf_iterator<char>(), [=](char s)
				{return vowels.find(s) != string::npos; });
			t.print();
			cout << "Количество гласных букв: " << count << endl;
		}
		else
		{
			cout << "Ошибка чтения файла";
		}
		book1.close();
		ifstream book2("voina-i-mir.txt");
		if (book2.is_open())
		{
			t.start("Способ 2");
			size_t count = count_if(istreambuf_iterator<char>(book2), istreambuf_iterator<char>(), [vowels](char s)
				{for (const auto& v : vowels)
			{
				if (v == s)
				{
					return true;
				}
			}
			return false;
				});
			t.print();
			cout << "Количество гласных букв: " << count << endl;
		}
		else
		{
			cout << "Ошибка чтения файла";
		}
		book2.close();
		ifstream book3("voina-i-mir.txt");
		if (book3.is_open())
		{
			size_t counter = 0;
			string str;
			t.start("Способ 3");
			while (getline(book3, str))
			{
				for (size_t i = 0; i < str.size(); i++)
				{
					if (vowels.find(str[i]) != string::npos)
					{
						counter++;
					}
				}
			}
			t.print();
			cout << "Количество гласных букв: " << counter << endl;
		}
		else
		{
			cout << "Ошибка чтения файла";
		}
		book3.close();
		ifstream book4("voina-i-mir.txt");
		if (book4.is_open())
		{
			size_t counter = 0;
			string str;
			t.start("Способ 4");
			while (getline(book4, str))
			{
				for (size_t i = 0; i < str.size(); i++)
				{
					for (size_t j = 0; j < vowels.size(); j++)
					{
						if (str[i] == vowels[j])
						{
							counter++;
						}
					}
				}
			}
			t.print();
			cout << "Количество гласных букв: " << counter << endl;
		}
		else
		{
			cout << "Ошибка чтения файла";
		}
		book4.close();
}

int main()
{
	//task1
	setlocale(LC_ALL, "Rus");
	int a = 10;
	int b = 15;
	int* aPtr = &a;
	int* bPtr = &b;
	cout << "aPtr = " << *aPtr << "\tbPtr = " << *bPtr << endl;
	cout << "Перемещение..." << endl;
	Swap(aPtr, bPtr);
	cout << "aPtr = " << *aPtr << "\tbPtr = " << *bPtr << endl;
	cout << endl;

	//task2
	int c = 20;
	int d = 10;
	int e = 35;
	int f = 35;
	int g = 2;

	int* cPtr = &c;
	int* dPtr = &d;
	int* ePtr = &e;
	int* fPtr = &f;
	int* gPtr = &g;

	cout << "Vector = ";
	vector <int*> v_Ptr = { cPtr, dPtr, ePtr, fPtr, gPtr };
	for (const auto& i : v_Ptr)
	{
		cout << *i << " ";
	}
	cout << endl;
	cout << "Сортировка..." << endl;
	SortPointers(v_Ptr);
	cout << "Vector = ";
	for (const auto& i : v_Ptr)
	{
		cout << *i << " ";
	}
	cout << endl;

	//task3
	ifstream book("voina-i-mir.txt");
	sortGls(book);
	return 0;
}

