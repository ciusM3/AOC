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
	int xOg, yOg;
};

void dfsFillExterior(char map[300][300], int mapSize, int x, int y)
{
	if (x < 0 || x >= mapSize || y < 0 || y >= mapSize)
		return;

	if (map[x][y] != '.')
		return;

	map[x][y] = 'O';

	dfsFillExterior(map, mapSize, x + 1, y);
	dfsFillExterior(map, mapSize, x - 1, y);
	dfsFillExterior(map, mapSize, x, y + 1);
	dfsFillExterior(map, mapSize, x, y - 1);
}

void fillExterior(char map[300][300], int mapSize)
{
	// flood fill from all sides
	for (int i = 0; i < mapSize; i++)
	{
		if (map[0][i] == '.')
			dfsFillExterior(map, mapSize, 0, i);
		if (map[mapSize - 1][i] == '.')
			dfsFillExterior(map, mapSize, mapSize - 1, i);
		if (map[i][0] == '.')
			dfsFillExterior(map, mapSize, i, 0);
		if (map[i][mapSize - 1] == '.')
			dfsFillExterior(map, mapSize, i, mapSize - 1);
	}
}

void sortXValues(redCoords* redPositions, int noPositions)
{
	sort(redPositions, redPositions + noPositions, [](const redCoords& a, const redCoords& b) {return a.x < b.x; });
}

void sortYValues(redCoords * redPositions, int noPositions)
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

	cout << "answer: " << maxSurfArea;
}

void part2()
{
	ifstream input("input.txt");

	char line[100];
	redCoords redPositions[500];

	int indexPos = 0;     // no of elements from input

	while (input >> line)
	{
		sscanf(line, "%d,%d", &redPositions[indexPos].y, &redPositions[indexPos].x);
		redPositions[indexPos].xOg = redPositions[indexPos].x;
		redPositions[indexPos].yOg = redPositions[indexPos].y;
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

	// create blank map
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
	for (int i = 0; i < mapSize; i++)
	{
		int first = -1;
		int last = -1;

		for (int j = 0; j < mapSize; j++)
		{
			if (map[i][j] == '#')
			{
				if (first == -1)
					first = j;
				last = j;
			}
		}

		if (first != -1 && last != -1 && first < last)
		{
			for (int j = first + 1; j < last; j++)
			{
				if (map[i][j] == '.')
					map[i][j] = 'X';
			}
		}
	}

	fillExterior(map, mapSize);

	// print map
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
			cout << map[i][j];
		cout << endl;
	}

	long long int maxSurfArea = -1;

	for (int i = 0; i < indexPos - 1; i++)
		for (int j = i + 1; j < indexPos; j++)
		{
			redCoords A = redPositions[i];
			redCoords C = redPositions[j];
			redCoords B = { C.x, A.y };
			redCoords D = { A.x, C.y };

			//see if rectangle is inside by following the edge of the current rectangle, if in its path there is O it means its not fully inside => skip
			int rectangleInside = 1;

			int smallestX, biggestX;
			int smallestY, biggestY;

			// edge A->B
			smallestX = MIN(A.x, B.x);
			biggestX = MAX(A.x, B.x);
			for (int i = smallestX; i <= biggestX && rectangleInside != 0; i++)
				if (map[i][A.y] == 'O')
					rectangleInside = 0;

			// edge C->D
			smallestX = MIN(C.x, D.x);
			biggestX = MAX(C.x, D.x);
			for (int i = smallestX; i <= biggestX && rectangleInside != 0; i++)
				if (map[i][C.y] == 'O')
					rectangleInside = 0;

			// edge A->D
			smallestY = MIN(A.y, B.y);
			biggestY = MAX(A.y, B.y);
			for (int i = smallestY; i <= biggestY && rectangleInside != 0; i++)
				if (map[A.x][i] == 'O')
					rectangleInside = 0;

			// edge B->C
			smallestY = MIN(B.y, C.y);
			biggestY = MAX(B.y, C.y);
			for (int i = smallestY; i <= biggestY && rectangleInside != 0; i++)
				if (map[C.x][i] == 'O')
					rectangleInside = 0;

			if (rectangleInside == 0)
				continue;

			long long int xDif = abs(A.xOg - C.xOg) + 1;
			long long int yDif = abs(A.yOg - C.yOg) + 1;

			long long int surfArea = xDif * yDif;

			if (surfArea > maxSurfArea)
				maxSurfArea = surfArea;
		}
	
	cout << endl << "answer: " << maxSurfArea;

}

int main()
{
	part1();
}