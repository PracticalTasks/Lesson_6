#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<ctime>
#include<algorithm>

using namespace std;
mutex mx;


template<typename T>
void _pcout(T val)
{
	lock_guard <mutex> lg(mx);
	cout << val << endl;
}

bool cmpPrimeNum(long long num)
{
	long long  end = sqrt(num);
	for (long long i = 2; i <= end; i++)
	{
		if ((num % i) == 0)
		{
			return false;
		}
	}
	return true;
}

int primeNumbers()
{
	std::cout << "Введите целое число: ";
	long long num = 2;
	int numOfPrimeNum = 0;
	std::cin >> numOfPrimeNum;
	int unit = numOfPrimeNum / 100;
	if (unit == 0)
		++unit;
	int count = 1;

	int i = 0;
	while (numOfPrimeNum != count)
	{
		num++;
		if (cmpPrimeNum(num))
		{
			if (++count % unit == 0)
			{
				system("cls");
				
				cout << "Прогресс вычесления: " << i++<<'%';
			}
				
		}
			
	}
	system("cls");
	cout << "Прогресс вычесления: 100%\n";
	cout << numOfPrimeNum << "-ое(ье) простое число: " << num << endl;
		return 0;
}

void addThing(vector<int> &vec)
{
	while (true)
	{
		this_thread::sleep_for(1s);
		if (vec.empty())
			break;
		lock_guard<mutex> lg(mx);
		vec.push_back(rand() % 10000);
		
	}

}

void getThing(vector<int> &vec)
{
	while (!vec.empty())
	{
		this_thread::sleep_for(0.5s);
		lock_guard<mutex> lg(mx);
		auto it = max_element(vec.begin(), vec.end());
		vec.erase(it);
	}

}

void countThing(vector<int>& vec)
{
	while (!vec.empty())
	{
		this_thread::sleep_for(1s);
		system("cls");
		lock_guard<mutex> lg(mx);
		cout << "Колличество оставшихся вещей: " << vec.size();
	}
	cout << endl;
}

int main()
{

	setlocale(0, "ru_RU.utf8");
	srand(time(nullptr));
	//Task 1
	{
		cout << "Task 1\n";
		auto pcout = [](auto val) { 
			_pcout(val);
		};

		thread td1(pcout, "hello 1");
		thread td2(pcout, 2);
		thread td3(pcout, 3.3f);
		td1.join();
		td2.join();
		td3.join();
	}

	//Task 2
	{
		cout << "\nTask 2\n";
		thread tdSecond(primeNumbers);
		tdSecond.join();
	}

	//Task 3
	{
		cout << "\nTask 3\n";
		vector<int> vec{ 123,324,32,5446,332,4356,765,3234,634,3434,4};
		auto aThing = [&]() {
			addThing(vec);
		};
		auto gThing = [&]() {
			getThing(vec);
		};
		auto cThing = [&]() {
			countThing(vec);
		};

		thread td1(aThing);
		thread td2(gThing);
		thread td3(cThing);
		td1.join();
		td2.join();
		td3.join();
		cout << "Вор вынес все вещи" << endl;
	}

}