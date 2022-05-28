#include "CellGeneration.h"

CellGeneration::~CellGeneration() {

	generation.clear();
	
	previousGeneration.clear();

}

CellGeneration::CellGeneration(int x, int y) {

	this->rows = x;
	this->cols = y;

}

vector<vector<Cell>> CellGeneration::GetGeneration() {
	return generation;
}

int CellGeneration::GetRows() {
	return rows;
}

int CellGeneration::GetCols() {
	return cols;
}

void CellGeneration::FillCellGeneration() {
	vector<vector<Cell>> newGeneration;
	if (previousGeneration.empty()) {
		newGeneration = FillFirstCellGeneration();
	}
	else {
		newGeneration = FillNextCellGeneration();
	}
	previousGeneration = generation;

	generation = newGeneration;
}


vector<vector<Cell>> CellGeneration::FillFirstCellGeneration() {
	vector<vector<Cell>> result(rows, vector<Cell>(cols)); // x - строки, y - столбцы

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Cell cell = Cell();
			result[i][j] = cell;
		}
	}

	return result;
}

int CellGeneration::Neighbor(int leftX, int leftY) { // передаются координаты соседа

	leftX = leftX < 0 ? leftX + rows : leftX % rows;
	leftY = leftY < 0 ? leftY + cols : leftY % cols;

	int stateNeightbour = generation[leftX][leftY].GetState();

	return stateNeightbour;
}

vector<int> CellGeneration::IdentifyNeighbors(int coordX, int coordY) {

	vector<int> neighbours;

	for (int leftX = coordX - 1; leftX <= coordX + 1; leftX++) {
		for (int leftY = coordY - 1; leftY <= coordY + 1; leftY++) {
			if (leftX != coordX || leftY != coordY) { // проверка на самого себя
				int stateNeightbour = Neighbor(leftX, leftY);
				if (stateNeightbour > 0) { // мёртвые клетки нет смысла учитывать как соседей
					neighbours.push_back(stateNeightbour);
				}
			}
		}
	}

	return neighbours;
}

vector<vector<Cell>> CellGeneration::FillNextCellGeneration() {

	vector<vector<Cell>> result(rows, vector<Cell>(cols)); // rows - количество строк, cols - количество столбцов

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			vector<int> neighbours = IdentifyNeighbors(i, j);
			Cell cell = Cell(generation[i][j].GetState(), neighbours);
			result[i][j] = cell;
		}
	}

	return result;
}

bool CellGeneration::CompareGeneration() {
	if (previousGeneration.empty()) {
		return 1;
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (previousGeneration[i][j].GetState() != generation[i][j].GetState()) {
				return 1;
			}
		}
	}

	return 0;
}
