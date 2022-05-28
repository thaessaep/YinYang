#pragma once
#include <iostream>
#include <vector>

#define YIN 1
#define YANG 2

using namespace std;

class Cell {

public:

	Cell();

	Cell(int previousState, vector<int> neighbours);

	int CellBirth(vector<int> neighbours);

	int CellDeath(vector<int> neighbours);

	void SetState(int state);

	int GetState();


private:

	int state;

};
