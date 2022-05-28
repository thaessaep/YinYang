#include "Cell.h"

Cell::Cell() {
	int randomState = rand() % 3;
	SetState(randomState);
}

Cell::Cell(int previousState, vector<int> neighbours) {

	if (previousState == 0 && neighbours.size() == 3) {
		int newState = CellBirth(neighbours);
		newState > 0 ? SetState(newState) : SetState(0);
	}
	else {
		int newState = CellDeath(neighbours);
		newState == 0 ? SetState(newState) : SetState(previousState);
	}

}

int Cell::CellBirth(vector<int> neighbours) {
	auto amountYin = count(neighbours.begin(), neighbours.end(), YIN);
	auto amountYang = count(neighbours.begin(), neighbours.end(), YANG);

	if (amountYin && amountYang) {
		if (amountYin > amountYang) {
			return YANG;
		}
		else {
			return YIN;
		}
	}

	return -1;
}

int Cell::CellDeath(vector<int> neighbours) {
	auto amountNeighbours = neighbours.size();
	auto amountYin = count(neighbours.begin(), neighbours.end(), YIN);
	auto amountYang = count(neighbours.begin(), neighbours.end(), YANG);

	if (amountNeighbours < 2 || amountNeighbours > 4) {
		return 0;
	}
	else if (amountNeighbours == 4) {
		if (amountYin != amountYang) {
			return 0;
		}
	}
	return -1;
}

void Cell::SetState(int state) {
	this->state = state;
}


int Cell::GetState() {
	return state;
}
