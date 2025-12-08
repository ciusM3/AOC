#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdio>
#include <math.h>

using namespace std;

typedef struct edgeStruct
{
	int firstNode;
	int secondNode;
	long long int cost;
};

typedef struct NS
{
	int key;
	struct NS* parent;
	int rank;
	int size;
	int x;
	int y;
	int z;
};

// disjointed sets func
NS* createNode(int val)
{
	NS* x = (NS*)malloc(sizeof(NS));
	x->key = val;
	x->parent = NULL;
	x->rank = 0;
	x->size = 1;
	return x;
}

void makeSet(NS* x)           // makes a set
{
	x->parent = x;
	x->rank = 0;
}

NS* findSet(NS* x)           // finds set representative
{
	if (x != x->parent)
		x->parent = findSet(x->parent);
	return x->parent;
}

void link(NS* x, NS* y)        // the function that helps unite sets
{
	if (x->rank > y->rank)
	{
		x->size += y->size;
		y->size = 0;
		y->parent = x;
	}
	else
	{
		y->size += x->size;
		x->size = 0;

		x->parent = y;
		if (x->rank == y->rank)
			y->rank++;
	}
}

void unionS(NS* x, NS* y)       // unites two sets
{
	link(findSet(x), findSet(y));
}


int distance(NS* boxes[1000], edgeStruct* edges, int boxesSize)     // calculates distance between two points
{
	int edgesIndex = 0;
	long long int  distance;

	for (int i = 0; i < boxesSize - 1; i++)
		for (int j = i + 1; j < boxesSize; j++)
		{
			long long int xAbs = abs(boxes[i]->x - boxes[j]->x);
			long long int yAbs = abs(boxes[i]->y - boxes[j]->y);
			long long int zAbs = abs(boxes[i]->z - boxes[j]->z);
			distance = xAbs * xAbs + yAbs * yAbs + zAbs * zAbs;

			edges[edgesIndex].firstNode = i;
			edges[edgesIndex].secondNode = j;
			edges[edgesIndex].cost = distance;
			edgesIndex++;
		}
	return edgesIndex;
}

void sortEdgesNewIter(edgeStruct* edges, int noEdges)
{
	sort(edges, edges + noEdges, [](const edgeStruct& a, const edgeStruct& b) {return a.cost < b.cost; });
}

long long int kruskal(edgeStruct edges[], NS* sets[1000], int noEdges, int noBoxes, int noConnections)
{
	int count = 1;

	sortEdgesNewIter(edges, noEdges);

	for (int i = 0; i < noConnections; i++)
	{
		int u = edges[i].firstNode;
		int v = edges[i].secondNode;

		if (findSet(sets[u]) != findSet(sets[v]))
		{
			unionS(sets[u], sets[v]);   // two circuits are linked

			count++;
		}
	}

	for (int i = 0; i < noBoxes - 1; i++)
	{
		for (int j = i + 1; j < noBoxes; j++)
			if (sets[i]->size < sets[j]->size)
			{
				NS* aux = sets[i];
				sets[i] = sets[j];
				sets[j] = aux;
			}
		if (sets[i]->size == 0)
			break;
	}

	for (int i = 0; i < noBoxes; i++)
		if (sets[i]->size != 0)
			cout << sets[i]->size << " ";
		else break;

	long long int answer = sets[0]->size * sets[1]->size * sets[2]->size;
	return answer;
}

void part1()
{
	ifstream input("input.txt");
	NS* boxesCoords[1000];

	int indexBoxes = 0;
	char line[100];

	while (input.getline(line, 100))
	{
		boxesCoords[indexBoxes] = createNode(indexBoxes);
		makeSet(boxesCoords[indexBoxes]);
		sscanf(line, "%d,%d,%d", &boxesCoords[indexBoxes]->x, &boxesCoords[indexBoxes]->y, &boxesCoords[indexBoxes]->z);
		indexBoxes++;
	}

	for (int i = 0; i < indexBoxes; i++)
		cout << i << ": " << boxesCoords[i]->x << " " << boxesCoords[i]->y << " " << boxesCoords[i]->z << endl;

	cout << endl;

	edgeStruct* edges = (edgeStruct*)malloc(2000000 * sizeof(edgeStruct));
	int noEdges = distance(boxesCoords, edges, indexBoxes);

	/*for (int i = 0; i < noEdges; i++)
	{
		cout << edges[i].firstNode << "->" << edges[i].secondNode << " with cost: " << edges[i].cost << endl;
	}*/

	long long int answer = kruskal(edges, boxesCoords, noEdges, indexBoxes, 1000);

	cout << endl << "answer: " << answer;
}

int main()
{
	part1();
}