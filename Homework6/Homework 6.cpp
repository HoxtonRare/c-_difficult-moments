#include <iostream>
#include <sstream>
#include <mutex>
#include <vector>
#include <random>

using namespace std;

//task 1

class pcout :
	public ostringstream
{
private:
	static mutex mCout;

public:
	~pcout()
	{
		lock_guard<mutex> guard(mCout);
		cout << this->str();
	}
};

mutex pcout::mCout;

void Thread1()
{
	pcout{} << "Многопоточность: поток 1" << endl;
}
void Thread2()
{
	pcout{} << "Многопоточность: поток 2" << endl;
}
void Thread3(size_t num)
{
	pcout{} << "Многопоточность: поток 3. Проход " << num+1 << endl;
}

//task 2

bool isPrime(unsigned long long result)
{
	if (result == 1) return false;
	for (size_t i = 2; i < sqrt(result); i++)
	{
		if (result % i == 0)
		{
			return false;
		}
	}
	return true;
}

void Prime(long long index, unsigned long long& result, long long& counter, bool& ready)
{
	while (counter < index)
	{
		result++;
		if (isPrime(result))
		{
			counter++;
		}
	}
	ready = true;
}

long long primeNumber(long long index)
{
	unsigned long long result = 0;
	long long counter = 0;
	bool ready = false;
	thread t2{ Prime, ref(index), ref(result), ref(counter), ref(ready) };
	while (!ready)
	{
		cout << "Прогресс: " << counter / (index / 100.0) << "%" << endl;
	}
	t2.join();
	cout << "Прогресс: " << counter / (index / 100.0) << "%" << endl;
	return result;
}

//task 3

mutex mutexHouse;

void master(vector<int>& things)
{
	while (!things.empty())
	{
		mutexHouse.lock();
		int new_thing = rand() % 100;
		things.push_back(new_thing);
		cout << "Хозяин принёс вещь стоимостью " << new_thing << endl;
		cout << "Стоимость вещей в доме: " << endl;
		for (const auto& t : things)
		{
			cout << t << " ";
		}
		cout << endl << endl;
		mutexHouse.unlock();
		this_thread::sleep_for(1000ms);
	}
}

void thief(vector<int>& things)
{
	while (!things.empty())
	{
		mutexHouse.lock();
		vector<int>::iterator high_price = max_element(things.begin(), things.end());
		cout << "Вор украл вещи стоимостью: " << *high_price << endl;
		things.erase(high_price);
		cout << "Остались вещи по цене: " << endl;
		for (const auto& n : things)
		{
			cout << n << " ";
		}
		cout << endl << endl;
		mutexHouse.unlock();
		this_thread::sleep_for(500ms);
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	//task 1
	cout << "\t\t TASK 1: " << endl;
	for (size_t i = 0, length = 3; i< length; i++)
	{
		thread t1{ Thread1 };
		thread t2{ Thread2 };
		thread t3{ Thread3, ref(i) };
		t1.join();
		t2.join();
		t3.join();
		pcout{} << endl;
	}

	//task 2
	cout << "\t\t TASK 2: " << endl;
	long long primeNumber№ = 1000;
	unsigned long long pNumber = primeNumber(primeNumber№);
	cout << primeNumber№ << "-ое простое число = " << pNumber << endl;

	//task 3
	cout << "\n\t\t TASK 3: " << endl;
	vector<int> things = { 5, 15, 55 };
	thread masterThread(master, ref(things));
	thread theifThread(thief, ref(things));
	masterThread.join();
	theifThread.join();
	cout << "Вор украл все вещи доме!" << endl;
	return 0;
}