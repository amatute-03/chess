#include <chrono>
#include <iostream>
#include <thread>
#include <stdio.h>
#include "piece.h"


using namespace std;

struct Node {
	char info;
	bool piecePresent;
	piece *pieceHeld = new piece;

	int xOffset;
	int yOffset;
	bool landingSpot;
	struct Node* up = NULL;
	struct Node* down = NULL;
	struct Node* left = NULL;
	struct Node* right = NULL;
};

void printMap();
void nodeDataPrintout(Node* node);
Node* movingAround(Node* node);
void nodePopulation();
void usePiece(Node* node);

Node* topLeft;
Node* topRight;
Node* bottomLeft;
Node* bottomRight;

int column = 0, row = 0;

Node* curr;
Node* selected;

int BISA = 0;
int BISB = 0;

char checks[] = {'#', '0'};
int pieceTypes[] = {1, 2, 3, 5, 4, 3, 2, 1,
					0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0,
					1, 2, 3, 4, 5, 3, 2, 1};
char sym[] = {'r', 'k', 'b', 'K', 'Q', 'b', 'k', 'r',
			  'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
			  'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
			  'r', 'k', 'b', 'Q', 'K', 'b', 'k', 'r'};
int PieceSetUp = 0;

Node* nodeCreation() {
	Node* rowPtr = topLeft;
	Node* temp = new Node;
	temp->landingSpot = false;

	BISA = ((BISA == 0) ? ((++BISB % 8 == 1) ? BISA : ++BISA) : ((++BISB % 8 == 1) ? BISA : --BISA));
	temp->info = checks[BISA];

	if(row < 2  || row > 5) {
		temp->piecePresent = true;
		temp->pieceHeld->setPieceType(sym[PieceSetUp]);
		temp->pieceHeld->setMoveType(pieceTypes[PieceSetUp++]);
		temp->pieceHeld->setSide(row < 2 ? 1 : 0);
		temp->pieceHeld->setPrefix("\033[2;47;35m");
		temp->pieceHeld->setSuffix("\033[0m");
	} 
	else {
		temp->piecePresent = false;
		temp->pieceHeld->setPrefix("");
		temp->pieceHeld->setSuffix("");
	}

	temp->xOffset = column;
	temp->yOffset = row;

	if(topLeft == NULL) {
		topLeft = temp;
		topRight = temp;
		bottomLeft = temp;
		bottomRight = temp;
		++column;
	}

	else if(column < 8 && row == 0){
		topRight->right = temp;
		temp->left = topRight;
		topRight = temp;
		++column;
	}
	else if(column < 8) {
		Node* tempA = topLeft;
		for(int i = 0; i < column; ++i) {
			tempA = tempA->right;
		}
		while(tempA->down != NULL) {
			tempA = tempA->down;
		}
		Node* tempB = tempA;
		temp->up = tempA;
		tempA->down = temp;
		if(tempA->left != NULL) {
			tempA = tempA->left;
			if(tempA->down != NULL) {
				tempA = tempA->down;
				temp->left = tempA;
				tempA->right = temp;
			}
		}
		if(column == 0) {
			bottomLeft = temp;
		}
		else {
			bottomRight = temp;
		}
		++column;
	}
	if(column == 8) {
		column = 0;
		++row;
	}

	return temp;
}

void nodePopulation() {
	Node* hold;
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			hold = nodeCreation();
		}
	}
}

void usePiece(Node* node) {
	node->piecePresent = true;
}

int argCount = 1;
char ** arguments = NULL;

int main(int argc, char ** argv) {
	arguments = argv;
	argCount = argc;

	cout << "\033[2J\033[1;1H";

	nodePopulation();

	movingAround(topLeft);

	return 0;
}




bool inPath(Node* node){
	if(selected != NULL) {
		if(node->piecePresent && node->pieceHeld->getSide() == selected->pieceHeld->getSide()) {
			return false;
		}
		if(selected->piecePresent) {
			Node* hold = selected;
			vector<vector<string>> dir = selected->pieceHeld->getMoveType();
			for(vector<string> b : dir) {
				for(string a : b) {
					for(int i = 0; i < a.size(); ++i) {
						if(hold == NULL) {
							break;
						}
						switch (int(a.at(i) - 48)) {
							case 1: {
								hold = hold->up;
								break;
							}
							case 2: {
								hold = hold->down;
								break;
							}
							case 3: {
								hold = hold->left;
								break;
							}
							case 4: {
								hold = hold->right;
								break;
							}
						}
					}
					if(hold != NULL && hold != node && hold->piecePresent) {
						hold = selected;
						break;
					}
					if(hold == node) {
						node->landingSpot = true;
						return true;
					}
					hold = selected;
				}
			}
		}
	}
	node->landingSpot = false;
	return false;
}





void movedPiece() {
	if(selected == curr) {
		return;
	}
	piece* hold = curr->pieceHeld;
	curr->pieceHeld = selected->pieceHeld;
	curr->piecePresent = true;
	selected->pieceHeld = hold;
	selected->piecePresent = false;
}





void printMap() {
	Node* temp = topLeft;
	Node* temp2 = topLeft;
	while(temp != NULL) {
		while(temp2 != NULL) {
			if(selected != NULL && selected->piecePresent && temp2 != curr) {
				if(selected == temp2) {
					if(temp2->piecePresent) {
						cout << "\033[42;30m" << temp2->pieceHeld->getPieceType() << " " << "\033[0m";
					}
					else {
						cout << "\033[42;30m" << temp2->info << " " << "\033[0m";;
					}
				} 
				else {
					if(inPath(temp2)) {
						if(temp2->piecePresent) {
							cout << "\033[45;30m" << temp2->pieceHeld->getPieceType() << " " << "\033[0m";
						} 
						else {
							cout << "\033[41;30m" << temp2->info << " " << "\033[0m";
						}
					} 
					else {
						if(temp2->piecePresent) {
							cout << "\033[100;30m" << temp2->pieceHeld->getPieceType() << " " << "\033[0m";
						} 
						else {
							cout << "\033[47;30m" << temp2->info << " " << "\033[0m";
						}
					}
				}
			} 
			else if(curr == temp2) {
				if(temp2->piecePresent) {
					cout << "\033[104;30m" << temp2->pieceHeld->getPieceType() << " " << "\033[0m";
				}
				else {
					cout << "\033[104;30m" << temp2->info << " " << "\033[0m";
				}
			} 
			else if(temp2->piecePresent) {
				cout << "\033[2;47;35m" << temp2->pieceHeld->getPieceType() << " " << "\033[0m";
			} 
			else {
				cout << temp2->info << " ";
			}
			temp2 = temp2->right;
		}
		cout << endl;
		temp = temp->down;
		temp2 = temp;
	}
	printf("\n");
}



void nodeDataPrintout(Node* node) {
	if(node != NULL) {
		cout << "\tnode: " << node->info;
		printf("\n\tside: %d\n", node->piecePresent != NULL ? node->pieceHeld->getSide() : -1);

		printf("\n\t%4c\n", node->up != NULL ? node->up->info : '-');
		printf("\t%2c", node->left != NULL ? node->left->info : '-');
		printf("%4c\n", node->right != NULL ? node->right->info : '-');
		printf("\t%4c", node->down != NULL ? node->down->info : '-');

		printf("\n\nselected: %c", selected != NULL ? selected->pieceHeld->getPieceType() : '-');


		cout << "\n\n\tpiece: " << node->piecePresent << endl;
		cout << "\n\tcolumn: " << node->xOffset;
		cout << "\n\trow: " << node->yOffset<< endl << endl;
	}
}

int uu, dd, ll, rr, nn;

Node* movingAround(Node* node) {
	using namespace this_thread;
	using namespace chrono;

	curr = node;
	int movement;
	cout << "1->up\t2->down\t3->left\t4->right\n5->select\t6->deselect\t0->exit\n" << endl;
	printMap();
	nodeDataPrintout(node);
	int ccc = 1;
	if (argCount != 1) {string h = arguments[ccc++];movement = int(h.at(0)-48);} else {cin >> movement;}
	while(movement != 0) {
		switch (movement) {
			case 1: {
				if(node->up != NULL) {
					++uu;
					node = node->up;
				}
				else {
					cout << "\t\tup is null" << endl;
				}
				break;
			}
			case 2: {
				if(node->down != NULL) {
					++dd;
					node = node->down;
				}
				else {
					cout << "\t\tdown is null" << endl;
				}
				break;
			}
			case 3: {
				if(node->left != NULL) {
					++ll;
					node = node->left;
				}
				else {
					cout << "\t\tleft is null" << endl;
				}
				break;
			}
			case 4: {
				if(node->right != NULL) {
					++rr;
					node = node->right;
				}
				else {
					cout << "\t\tright is null" << endl;
				}
				break;
			}
			case 5: {
				if(selected == NULL && node->piecePresent) {
					cout << "selected" << endl;
					selected = node;
				}
				else if(selected != NULL && node->landingSpot) {
					movedPiece();
					selected = NULL;
					cout << "entered" << endl;
				} else {
					cout << "invalid option" << endl;
				}
				break;
			}
			case 6: {
				if(selected != NULL) {
					cout << "deselected" << endl;
					node = selected;
					selected = NULL;
				}
				break;
			}
			default: {
				++nn;
				cout << "invalid entry" << endl;
				break;
			}
		}

		sleep_for(milliseconds(500));

		cout << "\033[2J\033[1;1H";

		curr = node;
		cout << "1->up\t2->down\t3->left\t4->right\n5->select\t6->deselect\t0->exit\n" << endl;
		printMap();
		nodeDataPrintout(node);
		if (argCount != 1) {string h = arguments[ccc++];movement = int(h.at(0)-48);} else {cin >> movement;}


		cout << "up: " << uu << endl;
		cout << "down: " << dd << endl;
		cout << "left: " << ll << endl;
		cout << "right: " << rr << endl;
		cout << "null: " << nn << endl;
	}

	cout << "exiting" << endl;
	return node;
}

