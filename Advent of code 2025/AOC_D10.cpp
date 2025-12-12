#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <string.h>

using namespace std;

typedef struct machine
{
	vector<int> diagram;
	vector<int> lights;
	vector< vector<int> > buttons;
	vector<int> joltage;
};

void buttonPress(vector<int>& lights, vector<int> button)
{
	for (int switchState : button)
	{
		lights[switchState] ^= 1;
	}
}

int bfs(vector<int> diagram, vector<int> lights, vector<vector<int>> buttons)
{
	queue<vector<int>> queue;
	set<vector<int>> visited;

	queue.push(lights);
	visited.insert(lights);

	int level = 0;

	while (!queue.empty())
	{
		int noElementsInLevel = queue.size();

		while (noElementsInLevel)
		{
			vector<int> current = queue.front();
			queue.pop();

			if (current == diagram)
				return level;

			for (vector<int> button : buttons)
			{
				vector<int> newLights = current;
				buttonPress(newLights, button);

				if (visited.find(newLights) == visited.end())
				{
					visited.insert(newLights);
					queue.push(newLights);
				}
			}
			noElementsInLevel--;
		}
		level++;
	}

	return -1; // not found
}

void part1()
{
	ifstream input("input.txt");

	char line[1000];
	int answer = 0;

	while (input.getline(line, 1000))
	{
		machine currentMachine;

		char* p = strtok(line, " ");

		while (p)
		{
			if (p[0] == '[')
			{
				for (int i = 1; i < strlen(p) - 1; i++)
				{
					if (p[i] == '#')
						currentMachine.diagram.push_back(1);
					else
						currentMachine.diagram.push_back(0);

					currentMachine.lights.push_back(0);
				}
			}
			else
				if (p[0] == '(')
				{
					vector<int> button;
					for (int i = 1; i < strlen(p) - 1; i++)
					{
						if (isdigit(p[i]))
							button.push_back(p[i] - '0');
					}
					currentMachine.buttons.push_back(button);
				}
				else
					if (p[0] == '{')
					{
						for (int i = 1; i < strlen(p) - 1; i++)
						{
							if (isdigit(p[i]))
								currentMachine.joltage.push_back(p[i] - '0');
						}
					}

			p = strtok(NULL, " ");
		}

		for (int i = 0; i < currentMachine.diagram.size(); i++)
			cout << currentMachine.diagram[i];
		cout << endl;

		answer += bfs(currentMachine.diagram, currentMachine.lights, currentMachine.buttons);

	}
	cout << endl << "answer: " << answer;
}

int main()
{
	part1();
}