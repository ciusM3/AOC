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
	int memoIndex;   // used for part 2, resolving with memoization
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

long long int dfsMemoized(node* currentNode, node* out, vector<int> &memo)
{
	if (memo[currentNode->memoIndex] != -1)
		return memo[currentNode->memoIndex];

	if (currentNode == out)
		return 1;

	currentNode->isVisited = 1;

	int noPaths = 0;

	for (node* i : currentNode->neighbours)
	{
		if (i->isVisited == 0)
			noPaths += dfsMemoized(i, out, memo);
	}

	if (memo[currentNode->memoIndex] == -1)     // store the number of paths to get to this node
		memo[currentNode->memoIndex] = noPaths;  

	currentNode->isVisited = 0;

	return noPaths;
}

void resetVisited(vector<node*> &nodes)
{
	for (node* i : nodes)
	{
		i->isVisited = 0;
	}
}

int searchPath(node* start, node* finish, vector<node*> &nodes, vector<int> &memo)
{
	resetVisited(nodes);

	for (int i = 0; i < memo.size(); i++) {
		memo[i] = -1;
	}

	return dfsMemoized(start, finish, memo);
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

	// solution
	node* you= nullptr;
	for (node* i : nodes)
	{
		if (i->name == "you")
		{
			you = i;
			break;
		}
	}

	resetVisited(nodes);

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
		aux->memoIndex = nodes.size();
		nodes.push_back(aux);
	}

	// add out as node, because it isn't present as one in input
	node* out = new node;
	out->name = "out";
	out->isVisited = 0;
	out->neighbours = {};
	out->memoIndex = nodes.size();
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

	// solution

	vector<int> memo;
	for (node* i : nodes)
		memo.push_back(-1);



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

	long long int svrToFft = searchPath(svr, fft, nodes, memo);
	long long int fftToDac = searchPath(fft, dac, nodes, memo);
	long long int dacToOut = searchPath(dac, out, nodes, memo);
	long long int answer = svrToFft * fftToDac * dacToOut;

	cout << "answer: " << answer;
}

int main()
{
	part2();
}