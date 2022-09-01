#include <iostream>
#include <clocale>
#include <list>
#include <vector>
#include <algorithm>
#include <iomanip>


using namespace std;

class Matrix {
	int m_size{};
	int** m_matrix{};
public:
	Matrix(int matrixSize) : m_size(matrixSize)
	{
		if (m_size <= 0)
		{
			cout << "Матрица не существует!" << endl;
			return;
		}
		m_matrix = new int* [m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_matrix[i] = new int[m_size];
		}
		for (size_t i = 0; i < m_size; i++)
		{
			for (size_t j = 0; j < m_size; j++)
			{
				m_matrix[i][j] = rand() % 100;
			}
		}
	}
	int** getMatrix() const
	{
		return m_matrix;
	}
	int getSize() const
	{
		return m_size;
	}
	~Matrix() 
	{
		for (int i = 0; i < getSize(); i++)
		{
			delete[] getMatrix()[i];
		}
		delete[] getMatrix();
	}
	double Determ(int** mtx, int size)
	{
		if (size == 1)
		{
			return mtx[0][0];
		}
		else if (size == 2)
		{
			return (mtx[0][0] * mtx[1][1]) - (mtx[0][1] * mtx[1][0]);
		}
		else
		{
			double determinate = 0;
			for (int k = 0; k < size; k++)
			{
				int** m = new int* [size - 1];
				for (int i = 0; i < size - 1; i++)
				{
					m[i] = new int[size - 1];
				}
				for (int i = 1; i < size; i++)
				{
					int t = 0;
					for (int j = 0; j < size; j++)
					{
						if (j == k)
						{
							continue;
						}
						m[i - 1][t] = mtx[i][j];
						t++;
					}
				}
				determinate += pow(-1, k + 2) * mtx[0][k] * Determ(m, size - 1);
			}
			return determinate;
		}
	}
	void Print() 
	{
		cout << setw(11) << "Матрица " << m_size << "x" << m_size << endl << setw(5);
		for (int i = 0; i < m_size; i++)
		{
			for (int j = 0; j < m_size; j++)
			{
				cout << m_matrix[i][j] << setw(5);
			}
			cout << endl;
		}
	}

};

void average(list<double> &ls)
{
	double ar{};
	for (auto i : ls)
	{
		ar += i;
	}
	ar /= ls.size();
	ls.push_back(ar);
}

template<typename T>
class MyIter{
private:
	T m_ptr;
public:
	MyIter() {}
	MyIter(T pos = 0) : m_ptr(pos) {}
	T operator*()
	{
		return m_ptr;
	}
	bool operator!= (MyIter<T> &val)
	{
		return m_ptr != val.m_ptr;
	}
	bool operator== (MyIter<T>& val)
	{
		return m_ptr == val.m_ptr;
	}
	MyIter& operator++()
	{
		++m_ptr;
		return *this;
	}
	MyIter& operator--()
	{
		m_ptr--;
		return *this;
	}
};

template <typename T>
class Range {
private:
	T m_begin;
	T m_end;
public:
	Range(T beg, T end) : m_begin(beg), m_end(end) {}
	MyIter<T> begin()
	{
		return MyIter<T>(m_begin);
	}
	MyIter<T> end()
	{
		return MyIter<T>(m_end);
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");
	//task 1
	cout << "\t\t TASK 1" << endl;
	list<double> ls = {1.5, 20, -13, 44, 2.3, 15.2, -6.2};
	for (auto i : ls)
		cout << i << " ";
	cout << endl;

	average(ls);
	for (auto i : ls)
		cout << i << " ";
	cout << "\n\n";

	//task 2
	cout << "\t\t TASK 2" << endl;
	cout << "Введите размер матрицы: " << endl;
	int size;
	cin >> size;
	Matrix m(size);
	m.Print();
	cout << endl << "Определитель матрицы = " << m.Determ(m.getMatrix(), m.getSize());
	cout << "\n\n";

	//task 3
	cout << "\t\t TASK 3" << endl;

	for (auto i : Range<int>{ 0, 10 })
	{
		cout << i << " ";
	}
	cout << "\n\n";
	return 0;
}