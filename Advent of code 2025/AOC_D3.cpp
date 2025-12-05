#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int getBiggestFromRange(int* arr, int l, int r)
{
	int index, max = -1;
	for (int i = l; i <= r; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			index = i;
		}
	}

	return index;
}

void part1()
{
	ifstream input("input.txt");
	char bank[101];
	int sizeOfBank;
	int sum = 0;

	while (input >> bank)
	{
		int joltage = 0;
		sizeOfBank = strlen(bank);
		int firstBiggest = -1, secondBiggest = -1;
		int indexFirst, indexSecond;
		int arr[100];

		for (int i = 0; i < sizeOfBank; i++)
			arr[i] = bank[i] - '0';

		indexFirst = getBiggestFromRange(arr, 0, sizeOfBank - 2);  // indexFirst = getBiggestFromRange(arr, 0, sizeOfBank - 1 - k);  recurrence formula (k is bigger the smalled the index is);
		indexSecond = getBiggestFromRange(arr, indexFirst + 1, sizeOfBank - 1);

		firstBiggest = arr[indexFirst];
		secondBiggest = arr[indexSecond];

		joltage = firstBiggest * 10 + secondBiggest;
		cout << joltage << endl;
		sum += joltage;
	}
	cout << "answer: " << sum;
}

void part2()
{
	ifstream input("input.txt");
	char bank[101];
	int sizeOfBank;
	long long int sum = 0;

	while (input >> bank)
	{
		long long int  joltage = 0;
		sizeOfBank = strlen(bank);
		long long int batteryValue = 0;
		long long int  batteryIndex = -1;
		long long int  prevBatteryIndex;
		int arr[100];

		for (int i = 0; i < sizeOfBank; i++)
			arr[i] = bank[i] - '0';

		for (int i = 0; i < 12; i++)
		{
			batteryIndex = getBiggestFromRange(arr, batteryIndex + 1, sizeOfBank - (12 - i));
			batteryValue = arr[batteryIndex];
			joltage = joltage * 10 + batteryValue;
		}

		cout << joltage << endl;
		sum += joltage;
	}
	cout << "answer: " << sum;
}

int main()
{
	part1();
}