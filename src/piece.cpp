#include "piece.h"
#include <string>


void piece::setPieceType(char type) {
	this->pieceType = type;
}

char piece::getPieceType() {
	return this->pieceType;
}

void piece::setMoveType(int type) {
	this->moveType = type;
}

int piece::getMoveVal() {
	return this->moveType;
}

vector<vector<string>> piece::getMoveType() {
	if(movements.size() == 0) {
		initMovements();
	}
	return this->movements.at(moveType);
}

void piece::setSide(int s) {
	this->side = s;
}

int piece::getSide() {
	return this->side;
}

bool piece::getPawnDoubleStep() {
	return this->pawnDoubleStep;
}

void piece::setPawnDoubleStep(bool s) {
	this->pawnDoubleStep = s;
}

char pieceType = '-';
int moveType;

void piece::initMovements() {

	movements.push_back({
		{"1", "11"},
		{"2", "22"},
		{"13"},
		{"14"},
		{"23"},
		{"24"}
	});

	movements.push_back({
		{"1", "11", "111", "1111", "11111", "111111", "1111111"},
		{"4", "44", "444", "4444", "44444", "444444", "4444444"},
		{"2", "22", "222", "2222", "22222", "222222", "2222222"},
		{"3", "33", "333", "3333", "33333", "333333", "3333333"}
	});

	movements.push_back({
		{"114"},
		{"441"},
		{"442"},
		{"224"},
		{"223"},
		{"332"},
		{"331"},
		{"113"}
	});

	movements.push_back({
		{"14", "1144", "111444", "11114444", "1111144444", "111111444444", "11111114444444"},
		{"24", "2244", "222444", "22224444", "2222244444", "222222444444", "22222224444444"},
		{"23", "2233", "222333", "22223333", "2222233333", "222222333333", "22222223333333"},
		{"13", "1133", "111333", "11113333", "1111133333", "111111333333", "11111113333333"}
	});

	movements.push_back({
		{"1", "11", "111", "1111", "11111", "111111", "1111111"},
		{"14", "1144", "111444", "11114444", "1111144444", "111111444444", "11111114444444"},
		{"4", "44", "444", "4444", "44444", "444444", "4444444"},
		{"24", "2244", "222444", "22224444", "2222244444", "222222444444", "22222224444444"},
		{"2", "22", "222", "2222", "22222", "222222", "2222222"},
		{"23", "2233", "222333", "22223333", "2222233333", "222222333333", "22222223333333"},
		{"3", "33", "333", "3333", "33333", "333333", "3333333"},
		{"13", "1133", "111333", "11113333", "1111133333", "111111333333", "11111113333333"}
	});

	movements.push_back({
		{"1"},
		{"14"},
		{"4"},
		{"24"},
		{"2"},
		{"23"},
		{"3"},
		{"13"}
	});
}
