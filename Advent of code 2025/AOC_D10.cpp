#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

using namespace std;

typedef struct machine
{
	char diagram[9];   // from what I've seen the number of lights is capped at 9, diagram is what lights should look like
	char lights[9];
	int buttons[100][9];  // rows are the buttons, cols affect the lights
	int joltage[1000];
	int noOfButtons, noOfLights, noOfJoltage;
};

void initMachine(machine* m)
{
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 9; j++)
			m->buttons[i][j] = -1;

	for (int i = 0; i < 9; i++)
		m->lights[i] = '.';           // in the beginning all lights are turned off
}

void printDiagram(machine m)
{
	for(int i=0; i<m.noOfLights;i++)
		cout << m.diagram[i];
	cout << endl;
}

int main()
{
	ifstream input("input.txt");

	char line[200];
	while (input.getline(line, 200))
	{
		machine m;
		initMachine(&m);

		cout << line << endl;
		char* p = strtok(line, " ");

		memcpy(m.diagram, line + 1, strlen(line) - 2);   // the first will always be the diagram
		m.noOfLights = strlen(line) - 2;

		printDiagram(m);
		
		while (p != NULL)
		{
			p = strtok(NULL, " ");
		}
	}
}