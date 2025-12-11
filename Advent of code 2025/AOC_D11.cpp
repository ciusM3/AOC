#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

typedef struct node
{
	string name;
	vector<node*> neighbours;
	int isVisited;
};

int dfs(node* currentNode, node* out)
{
	if (currentNode == out)
		return 1;

	currentNode->isVisited = 1;

	int noPaths = 0;

	for (node* i : currentNode->neighbours)
	{
		if (i->isVisited == 0)
			noPaths += dfs(i, out);
	}

	currentNode->isVisited = 0;

	return noPaths;
}

void part1()
{
	ifstream input("input.txt");

	char line[1000];
	char inputCopy[600][1000];
	int inputIndex = 0;

	vector<node*> nodes;
	
	while (input.getline(line, 1000))
	{
		strcpy(inputCopy[inputIndex], line);     // make a copy of the input to help create connections
		inputIndex++;

		// first element is always original node
		node* aux = new node;
		char* p = strtok(line, ":");
		aux->name = string(p);
		aux->neighbours = {};
		aux->isVisited = 0;
		nodes.push_back(aux);
	}

	// add out as node, because it isn't present as one in input
	node* out = new node;
	out->name = "out";
	out->isVisited = 0;
	out->neighbours = {};
	nodes.push_back(out);

	// connect the graph
	for (int i = 0; i < inputIndex; i++)
	{
		char* p = strtok(inputCopy[i], ":");
		p = strtok(NULL, " ");
		while (p)
		{
			for (node* j : nodes)
			{
				if (j->name == string(p))
				{
					nodes[i]->neighbours.push_back(j);
					break;
				}
			}
			p = strtok(NULL, " ");
		}
	}

	node* you= nullptr;
	for (node* i : nodes)
	{
		if (i->name == "you")
		{
			you = i;
			break;
		}
	}

	for (node* i : nodes)
	{
		i->isVisited = 0;
	}

	int count = dfs(you, out);

	cout << "answer: " << count;
}

void part2()
{
	ifstream input("input.txt");

	char line[1000];
	char inputCopy[600][1000];
	int inputIndex = 0;

	vector<node*> nodes;

	while (input.getline(line, 1000))
	{
		strcpy(inputCopy[inputIndex], line);     // make a copy of the input to help create connections
		inputIndex++;

		// first element is always original node
		node* aux = new node;
		char* p = strtok(line, ":");
		aux->name = string(p);
		aux->neighbours = {};
		aux->isVisited = 0;
		nodes.push_back(aux);
	}

	// add out as node, because it isn't present as one in input
	node* out = new node;
	out->name = "out";
	out->isVisited = 0;
	out->neighbours = {};
	nodes.push_back(out);

	// connect the graph
	for (int i = 0; i < inputIndex; i++)
	{
		char* p = strtok(inputCopy[i], ":");
		p = strtok(NULL, " ");
		while (p)
		{
			for (node* j : nodes)
			{
				if (j->name == string(p))
				{
					nodes[i]->neighbours.push_back(j);
					break;
				}
			}
			p = strtok(NULL, " ");
		}
	}

	node* svr = nullptr;
	node* dac = nullptr;
	node* fft = nullptr;
	for (node* i : nodes)
	{
		if (i->name == "svr")
			svr = i;
		if (i->name == "dac")
			dac = i;
		if (i->name == "fft")
			fft = i;
	}

	for (node* i : nodes)
	{
		i->isVisited = 0;
	}

	int count = dfs(svr, out);

	cout << "answer: " << count;
}

int main()
{
	part1();
}