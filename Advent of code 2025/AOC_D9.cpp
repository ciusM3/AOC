#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <fstream>
#include <cstdio>
#include <math.h>
#include <algorithm>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

using namespace std;

typedef struct redCoords
{
	int x;
	int y;
};

void sortXValues(redCoords* redPositions, int noPositions)
{
	sort(redPositions, redPositions + noPositions, [](const redCoords& a, const redCoords& b) {return a.x < b.x; });
}

void sortYValues(redCoords* redPositions, int noPositions)
{
	sort(redPositions, redPositions + noPositions, [](const redCoords& a, const redCoords& b) {return a.y < b.y; });
}

void uniqueifyX(redCoords* redPositions, int noPositions)
{
	int currentIndex = -1;
	for (int i = 0; i < noPositions; i++)
	{
		currentIndex++;
		int currentVal = redPositions[i].x;
		redPositions[i].x = currentIndex;
		i++;
		while (redPositions[i].x == currentVal)
		{
			redPositions[i].x = currentIndex;
			i++;
		}
		i--;
	}
}

void uniqueifyY(redCoords* redPositions, int noPositions)
{
	int currentIndex = -1;
	for (int i = 0; i < noPositions; i++)
	{
		currentIndex++;
		int currentVal = redPositions[i].y;
		redPositions[i].y = currentIndex;
		i++;
		while (redPositions[i].y == currentVal)
		{
			redPositions[i].y = currentIndex;
			i++;
		}
		i--;
	}
}

void minimize(redCoords* redPositions, int noPositions)
{
	sortXValues(redPositions, noPositions);
	uniqueifyX(redPositions, noPositions);
	sortYValues(redPositions, noPositions);
	uniqueifyY(redPositions, noPositions);
}

int getBiggestVal(redCoords* redPositions, int noPositions)
{
	if (redPositions[noPositions - 1].x > redPositions[noPositions - 1].y)
		return redPositions[noPositions - 1].x;
	else
		return redPositions[noPositions - 1].y;
}

int getSmallestVal(redCoords* redPositions, int noPositions)
{
	if (redPositions[noPositions - 1].x < redPositions[noPositions - 1].y)
		return redPositions[noPositions - 1].x;
	else
		return redPositions[noPositions - 1].y;
}

void part1()
{
	ifstream input("input.txt");

	char line[100];
	redCoords redPositions[500];
	int indexPos = 0;     // no of elements from input

	while (input >> line)
	{
		sscanf(line, "%d,%d", &redPositions[indexPos].y, &redPositions[indexPos].x);
		indexPos++;
	}

	for (int i = 0; i < indexPos; i++)
		cout << redPositions[i].y << " " << redPositions[i].x << endl;

	long long int maxSurfArea = -1;

	for (int i = 0; i < indexPos - 1; i++)
		for (int j = i + 1; j < indexPos; j++)
		{
			redCoords A = redPositions[i];
			redCoords C = redPositions[j];

			long long int xDif = abs(A.x - C.x) + 1;
			long long int yDif = abs(A.y - C.y) + 1;

			long long int surfArea = xDif * yDif;

			if (surfArea > maxSurfArea)
				maxSurfArea = surfArea;
		}

	cout << maxSurfArea;
}

void part2()
{
	ifstream input("input.txt");

	char line[100];
	redCoords redPositions[500];
	redCoords redPositionsBig[500];
	int indexPos = 0;     // no of elements from input

	while (input >> line)
	{
		sscanf(line, "%d,%d", &redPositions[indexPos].y, &redPositions[indexPos].x);
		redPositionsBig[indexPos].y = redPositions[indexPos].y;
		redPositionsBig[indexPos].x = redPositions[indexPos].x;
		indexPos++;
	}

	for (int i = 0; i < indexPos; i++)
		cout << redPositions[i].y << " " << redPositions[i].x << endl;

	cout << endl;

	minimize(redPositions, indexPos);
	int mapSize = getBiggestVal(redPositions, indexPos) + 1;
	cout << "mapSize post minimization: " << mapSize << endl << endl;

	for (int i = 0; i < indexPos; i++)
		cout << redPositions[i].y << " " << redPositions[i].x << endl;

	char map[300][300];

	cout << endl;

	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
			map[i][j] = '.';
	}
	
	// create the borders 
	for (int i = 0; i < indexPos; i++)
	{
		redCoords corner = redPositions[i];
		map[corner.x][corner.y] = '#';
	}

	// fill for vertical
	for (int i = 1; i < indexPos; i++)
	{
		redCoords A = redPositions[i];
		redCoords C = redPositions[i - 1];

		int smallest, biggest;
		
		if (A.y == C.y)
		{
			smallest = MIN(A.x, C.x) + 1;
			biggest = MAX(A.x, C.x);
			for (int i = smallest; i < biggest; i++)
			{
				map[i][A.y] = 'X';
			}
		}
	}

	// fill for horizontal
	for (int row = 0; row < mapSize; row++)
	{
		int first = -1;
		int last = -1;

		for (int col = 0; col < mapSize; col++)
		{
			if (map[row][col] == '#')
			{
				if (first == -1)
					first = col;
				last = col;
			}
		}

		if (first != -1 && last != -1 && first < last)
		{
			for (int col = first + 1; col < last; col++)
			{
				if (map[row][col] == '.')
					map[row][col] = 'X';
			}
		}
	}

	// fill out



	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
			cout << map[i][j];
		cout << endl;
	}
}

int main()
{
	part2();
}