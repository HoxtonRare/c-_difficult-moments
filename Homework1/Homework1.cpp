#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <optional>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct Person {
	string surname;
	string name;
	optional<string> middleName;
};

struct PhoneNumber {
	int codeOfCountry;
	int codeOfCity;
	string number;
	optional<int> additNumber;
};

bool operator < (const Person& ps1, const Person& ps2)
{
	return tie(ps1.surname, ps1.name, ps1.middleName) < tie(ps2.surname, ps2.name, ps2.middleName);
}

bool operator == (const Person& ps1, const Person& ps2)
{
	return tie(ps1.surname, ps1.name, ps1.middleName) == tie(ps2.surname, ps2.name, ps2.middleName);
}

bool operator == (const PhoneNumber& ph1, const PhoneNumber& ph2)
{
	return tie(ph1.codeOfCountry, ph1.codeOfCity, ph1.number, ph1.additNumber) == tie(ph2.codeOfCountry, ph2.codeOfCity, ph2.number, ph2.additNumber);
}

bool operator < (const PhoneNumber& ph1, const PhoneNumber& ph2)
{
	return tie(ph1.codeOfCountry, ph1.codeOfCity, ph1.number, ph1.additNumber) < tie(ph2.codeOfCountry, ph2.codeOfCity, ph2.number, ph2.additNumber);
}

class PhoneBook {
	vector<pair<Person, PhoneNumber> > book;
public:
	PhoneBook(ifstream& file) {
		Person ps;
		PhoneNumber ph;
		if (!file.is_open())
			cout << "Ошибка!" << endl;
		else
		{
			string line;
			while (!file.eof())
			{
				getline(file, line);
				stringstream in(line);
				in >> ps.surname;
				in >> ps.name;
				if (in.getline(&line[0], in.tellg(), ' '))
				{
					if (in.peek() != '+')
					{
						in >> ps.middleName.emplace();
					}
					else
					{
						ps.middleName.reset();
					}
				}
				in >> ph.codeOfCountry;
				if (in.getline(&line[0], in.tellg(), '('))
				{
					in >> ph.codeOfCity;
				}
				if (in.getline(&line[0], in.tellg(), ')'))
				{
					in >> ph.number;
				}
				if (!in.eof())
				{
					in >> ph.additNumber.emplace();
				}
				else
				{
					ph.additNumber.reset();
				}
				book.push_back(make_pair(ps, ph));
			}
			file.close();
		}
	}

	void SortByName()
	{
		sort(book.begin(), book.end(), [](auto& x, auto& y) {return x.first < y.first; });
	}
	void SortByPhone()
	{
		sort(book.begin(), book.end(), [](auto& x, auto& y) {return x.second < y.second; });
	}
	tuple<string, PhoneNumber> GetPhoneNumber(string surname) {
		vector<pair<Person, PhoneNumber>>::iterator it;
		tuple<string, PhoneNumber> temp_tuple;

		int sum = 0;
		PhoneNumber ph;

		for (it = book.begin(); it != book.end(); it++)
		{
			if (it->first.surname == surname)
			{
				sum++;
				ph = it->second;
			}
		}

		switch (sum) {
		case 0:
			temp_tuple = make_tuple("Не найден", ph);
			break;
		case 1:
			temp_tuple = make_tuple("", ph);
			break;
		default:
			temp_tuple = make_tuple("Найдено больше одного", ph);
			break;
		}

		return temp_tuple;
	}
	void ChangePhoneNumber(Person ps, PhoneNumber nPh)
	{
		vector<pair<Person, PhoneNumber>>::iterator it;
		for (it = book.begin(); it != book.end(); it++)
		{
			if (it->first == ps)
			{
				it->second = nPh;
			}
		}
	}
	friend ostream& operator<<(ostream& os, PhoneBook& book);
};

ostream &operator << (ostream& os,const Person& ps)
{
	os << ps.surname << " " << ps.name << " ";
	if (ps.middleName.has_value())
	{
		os << ps.middleName.value();
	}
	return os;
}

ostream& operator <<(ostream& os, const PhoneNumber ph)
{
	os << "+" << ph.codeOfCountry << "(" << ph.codeOfCity << ")" << ph.number << " ";
	if (ph.additNumber.has_value())
	{
		os << ph.additNumber.value();
	}
	return os;
}

ostream& operator<<(ostream& os, PhoneBook& Phonebook)
{
	vector<pair<Person, PhoneNumber>>::iterator it;

	for (it = Phonebook.book.begin(); it != Phonebook.book.end(); it++)
	{
		os << it->first << " " << it->second << endl;
	}

	return os;
}

int main() {
	setlocale(LC_ALL, "rus");
	ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt
	PhoneBook book(file);
	cout << book;
	cout << "------SortByPhone-------" << endl;
	book.SortByPhone();
	cout << book;
	cout << "------SortByName--------" << endl;
	book.SortByName();
	cout << book;
	cout << "-----GetPhoneNumber-----" << endl;
		auto print_phone_number = [&book](const string& surname) {
		cout << surname << "\t";
		auto answer = book.GetPhoneNumber(surname);
		if (get<0>(answer).empty())
			cout << get<1>(answer);
		else
			cout << get<0>(answer);
		cout << endl;
	};
	print_phone_number("Иванов");
	print_phone_number("Петров");
	cout << "----ChangePhoneNumber----" << endl;
	book.ChangePhoneNumber(Person{ "Котов", "Василий", "Елисееевич" },
		PhoneNumber{ 7, 123, "15344458", nullopt });
	book.ChangePhoneNumber(Person{ "Миронова", "Маргарита", "Александровна" },
		PhoneNumber{ 16, 465, "9155448", 13 });
	cout << book;
	return 0;
}