#pragma once
#include <ctime>
#include "Cell.h"

using namespace std;

class CellGeneration {

public:

	CellGeneration(int x = 50, int y = 50);

	~CellGeneration();

	vector<vector<Cell>> GetGeneration();

	int GetRows();

	int GetCols();

	void FillCellGeneration();

	vector<vector<Cell>> FillFirstCellGeneration();

	vector<vector<Cell>> FillNextCellGeneration();

	vector<int> IdentifyNeighbors(int coordX, int coordY);

	int Neighbor(int coordX, int coordY);

	bool CompareGeneration();


private:

	int rows, cols;
	vector<vector<Cell>> generation;
	vector<vector<Cell>> previousGeneration;

};

