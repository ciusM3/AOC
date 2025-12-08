#define _CRT_SECURE_NO_WARNINGS

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
	int cost;
};

typedef struct NS
{
	int key;
	struct NS* parent;
	int rank;
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
		y->parent = x;
	else
	{
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
			distance = pow(xAbs, 2) + pow(yAbs, 2) + pow(zAbs, 2);

			edges[edgesIndex].firstNode = i;
			edges[edgesIndex].secondNode = j;
			edges[edgesIndex].cost = distance;
			edgesIndex++;
		}
	return edgesIndex;
}

void sortEdges(edgeStruct* edges, int noEdges)
{
	for (int i = 0; i < noEdges - 1; i++)
		for (int j = i + 1; j < noEdges; j++)
			if (edges[i].cost > edges[j].cost)
			{
				edgeStruct aux = edges[i];
				edges[i] = edges[j];
				edges[j] = aux;
			}
}

void kruskal(edgeStruct edges[], NS* sets[1000], int noEdges, int noBoxes)
{
	int circuits[1000];

	for (int i = 0; i < noBoxes; i++)  // in the beginning every box is its own circuit
		circuits[i] = 1;

	int count = 0;

	for (int i = 0; i < noEdges && count<10; i++)
	{
		int u = edges[i].firstNode;
		int v = edges[i].secondNode;

		if (findSet(sets[u]) != findSet(sets[v]))
		{
			int createdCircuitSize = circuits[findSet(sets[u])->key] + circuits[findSet(sets[v])->key];

			circuits[findSet(sets[u])->key] = 0;
			circuits[findSet(sets[v])->key] = 0;

			unionS(sets[u], sets[v]);   // two circuits are linked

			NS* circuitRepresentative = findSet(sets[u]);

			circuits[circuitRepresentative->key] = createdCircuitSize;
			count++;
		}
	}
	
	for (int i = 0; i < noBoxes - 1; i++)
		for (int j = i + 1; j < noBoxes; j++)
			if (circuits[i] < circuits[j])
			{
				int aux = circuits[i];
				circuits[i] = circuits[j];
				circuits[j] = aux;
			}

	for (int i = 0; i < noBoxes; i++)
		cout << circuits[i] << " ";

	/*int max1, max2, max3;
	max1 = max2 = max3 = circuits[0];
	for (int i = 0; i < noBoxes; i++)
	{
		if (circuits[i] > max1) {
			max3 = max2;
			max2 = max1;
			max1 = circuits[i];
		}
		else if (circuits[i] > max2) {
			max3 = max2;
			max2 = circuits[i];
		}
		else if (circuits[i] > max3)
			max3 = circuits[i];
	}*/

	/*long long int answer;
	answer = max1 * max2 * max3;

	return answer;*/
}

void part1()
{
	ifstream input("input.txt");
	NS* boxesCoords[1000];

	int indexBoxes = 0;
	char line[100];

	while (input.getline(line,100))
	{
		boxesCoords[indexBoxes] = createNode(indexBoxes);
		makeSet(boxesCoords[indexBoxes]);
		sscanf(line, "%d,%d,%d", &boxesCoords[indexBoxes]->x, &boxesCoords[indexBoxes]->y, &boxesCoords[indexBoxes]->z);
		indexBoxes++;
	}

	for (int i = 0; i < indexBoxes; i++)
		cout << i << ": " << boxesCoords[i]->x << " " << boxesCoords[i]->y << " " << boxesCoords[i]->z << endl;

	cout << endl;

	edgeStruct* edges = (edgeStruct*)malloc(1000000 * sizeof(edgeStruct));
	int noEdges = distance(boxesCoords, edges, indexBoxes);

	sortEdges(edges, noEdges);

	for (int i = 0; i < noEdges; i++)
	{
		cout << edges[i].firstNode << "->" << edges[i].secondNode << " with cost: " << edges[i].cost << endl;
	}

	kruskal(edges, boxesCoords, noEdges, indexBoxes);

	//long long int answer = kruskal(edges, boxesCoords, noEdges, indexBoxes);

	//cout << endl << "answer: " << answer;
}

int main()
{
	part1();
}