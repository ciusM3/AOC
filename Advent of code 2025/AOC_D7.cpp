#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std; 

char** createMap(int &noRows, int &noCols)
{
	ifstream input("input.txt");
	char line[1000];

	input.getline(line, 1000);

	// finding the size of map
	noCols = strlen(line) + 1;

	// allocating map on heap
	char** map = (char**)malloc(noCols * sizeof(char*));
	for (int i = 0; i < noCols; i++)
			map[i] = (char*)malloc(noCols * sizeof(char));

	// for the first line of the map cause I read it for the size
	for (int j = 0; j < strlen(line); j++)
		map[0][j] = line[j];


	//  finishing copying elements to map
	noRows = 1;

	while (input.getline(line, 1000))
	{
		for (int j = 0; j < strlen(line); j++)
			map[noRows][j] = line[j];
		noRows++;
	}

	noCols -= 1; // because its almost a perfect square 2d array but noCols are -1

	return map;
}

void printMap(char** map, int noRows, int noCols)
{
	for (int i = 0; i < noRows; i++)
	{
		for (int j = 0; j < noCols; j++)
			cout << map[i][j];
		cout << endl;
	}
}

int getStart(char** map, int noCols)
{
	for (int j = 0; j < noCols; j++)
		if (map[0][j] == 'S')
			return j;
	return -1; // not found
}

int tachyonSplit(char** map, int currentCol, int currentRow, int noRows, int noCols)
{
	if (currentRow == noRows-1)
		return 0;

	if (map[currentRow + 1][currentCol] == '|') // if the next element is a beam, stop this branch and go next
		return 0;

	//printMap(map, noRows, noCols);   // only for the example, the puzzle input takes too much
	//cout << endl;

	if (map[currentRow + 1][currentCol] == '.')  // if the beam can pass straight down I put | and continue to the next row
	{
		if(map[currentRow + 1][currentCol] == '.')
			map[currentRow + 1][currentCol] = '|';
		return tachyonSplit(map, currentCol, currentRow + 1, noRows, noCols);
	}
	else
		if (map[currentRow + 1][currentCol - 1] != '|' && map[currentRow + 1][currentCol + 1] != '|')  // there is a splitter, if there aren't beams that means it can be split in 2
		{
			map[currentRow + 1][currentCol-1] = '|';
			map[currentRow + 1][currentCol + 1] = '|';
			return 2 + tachyonSplit(map, currentCol - 1, currentRow + 1, noRows, noCols) + tachyonSplit(map, currentCol + 1, currentRow + 1, noRows, noCols);
		}
		else
			if (map[currentRow + 1][currentCol - 1] == '|' && map[currentRow + 1][currentCol + 1] != '|')  // there is a splitter, but a beam already passed the left column. 
			{																							  // The algorithm always makes the left branch of beams first, so no need to check the right branch.
				map[currentRow + 1][currentCol + 1] = '|';
				return 1 + tachyonSplit(map, currentCol + 1, currentRow + 1, noRows, noCols);
			}
	
}



int noOfSplitersHit(char** map, int noRows, int noCols)
{
	int count = 0;
	for (int i = 1; i < noRows; i++)
	{
		for (int j = 0; j < noCols; j++)
			if (map[i][j] == '^' && map[i-1][j]=='|')
				count++;
	}
	return count;
}

void part1()
{
	int noRows, noCols;
	char** map = createMap(noRows, noCols);


	int start = getStart(map, noCols);
	
	int noOfSliptLines = tachyonSplit(map, start, 0, noRows, noCols);
	int answer = noOfSplitersHit(map, noRows, noCols);
	printMap(map, noRows, noCols);

	cout << "answer: " << answer << endl;
	
}

int main()
{
	part1();
}