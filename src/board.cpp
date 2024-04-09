
#include <iostream>
#include <glad/glad.h>

#include "GLSL.h"
#include "Program.h"
#include "Shape.h"
#include "MatrixStack.h"
#include "WindowManager.h"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>





#include <chrono>
// #include <iostream>
#include <thread>
#include <stdio.h>
#include "piece.h"




using namespace std;
using namespace glm;


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



// #include <chrono>
// #include <iostream>
// #include <thread>
// #include <stdio.h>
// #include "piece.h"


// using namespace std;

// struct Node {
// 	char info;
// 	bool piecePresent;
// 	piece *pieceHeld = new piece;

// 	int xOffset;
// 	int yOffset;
// 	bool landingSpot;
// 	struct Node* up = NULL;
// 	struct Node* down = NULL;
// 	struct Node* left = NULL;
// 	struct Node* right = NULL;
// };

// void printMap();
// void nodeDataPrintout(Node* node);
// Node* movingAround(Node* node);
// void nodePopulation();
// void usePiece(Node* node);

extern "C" {
    void printMap();
    void nodeDataPrintout(Node* node);
    Node* movingAround(Node* node);
    void nodePopulation();
    void usePiece(Node* node);
	Node* nodeCreation();
	bool inPath(Node* node);
	void movedPiece();
	Node* getTL();
	Node* getTR();
	Node* getBL();
	Node* getBR();
	Node* getCURR();
	Node* getSEL();
	Node* moveHelperRET(int m, Node * n);
}


Node* topLeft;
Node* topRight;
Node* bottomLeft;
Node* bottomRight;

int column = 0, row = 0;

Node* curr;
Node* selected;


Node* getTL() {
    return topLeft;
}
Node* getTR() {
    return topRight;
}
Node* getBL() {
    return bottomLeft;
}
Node* getBR() {
    return bottomRight;
}
Node* getCURR() {
    return curr;
}
Node* getSEL() {
    return selected;
}


int BISA = 0;
int BISB = 0;

char checks[] = {'0', '#'};
int pieceTypes[] = {1, 2, 3, 5, 4, 3, 2, 1,
					0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0,
					1, 2, 3, 5, 4, 3, 2, 1};
char sym[] = {'r', 'k', 'b', 'K', 'Q', 'b', 'k', 'r',
			  'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
			  'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
			  'r', 'k', 'b', 'K', 'Q', 'b', 'k', 'r'};
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


// void moveHelper(int m, Node * n) {
// 	switch (m) {
// 			case 1: {
// 				if(n->up != NULL) {
// 					n = n->up;
// 				}
// 				break;
// 			}
// 			case 2: {
// 				if(n->down != NULL) {
// 					n = n->down;
// 				}
// 				break;
// 			}
// 			case 3: {
// 				if(n->left != NULL) {
// 					n = n->left;
// 				}
// 				break;
// 			}
// 			case 4: {
// 				if(n->right != NULL) {
// 					n = n->right;
// 				}
// 				break;
// 			}
// 			case 5: {
// 				if(selected == NULL && n->piecePresent) {
// 					selected = n;
// 				}
// 				else if(selected != NULL && n->landingSpot) {
// 					movedPiece();
// 					selected = NULL;
// 				}
// 				break;
// 			}
// 			case 6: {
// 				if(selected != NULL) {
// 					n = selected;
// 					selected = NULL;
// 				}
// 				break;
// 			}
// 		}
// }







Node * moveHelperRET(int m, Node * n) {
	switch (m) {
			case 1: {
				if(n->up != NULL) {
					n = n->up;
				}
				break;
			}
			case 2: {
				if(n->down != NULL) {
					n = n->down;
				}
				break;
			}
			case 3: {
				if(n->left != NULL) {
					n = n->left;
				}
				break;
			}
			case 4: {
				if(n->right != NULL) {
					n = n->right;
				}
				break;
			}
			case 5: {
				if(selected == NULL && n->piecePresent) {
					selected = n;
				}
				else if(selected != NULL && n->landingSpot) {
					movedPiece();
					selected = NULL;
				}
				break;
			}
			case 6: {
				if(selected != NULL) {
					n = selected;
					selected = NULL;
				}
				break;
			}
		}

	return n;
}


Node* movingAround(Node* node) {
	using namespace this_thread;
	using namespace chrono;

	curr = node;
	int movement;
	cout << "1->up\t2->down\t3->left\t4->right\n5->select\t6->deselect\t0->exit\n" << endl;
	printMap();
	nodeDataPrintout(node);
	int ccc = 1;
	cin >> movement;
	while(movement != 0) {
		
		node = moveHelperRET(movement, node);

		sleep_for(milliseconds(500));

		cout << "\033[2J\033[1;1H";

		curr = node;
		cout << "1->up\t2->down\t3->left\t4->right\n5->select\t6->deselect\t0->exit\n" << endl;
		printMap();
		nodeDataPrintout(node);
		cin >> movement;

	}

	cout << "exiting" << endl;
	return node;
}


























class Application : public EventCallbacks
{

public:

	WindowManager * windowManager = nullptr;

	// Our shader program
	std::shared_ptr<Program> prog;

	// Shape to be used (from obj file)
	shared_ptr<Shape> shape;
	shared_ptr<Shape> cube;

	// location
	// shared_ptr<Shape> SmoothSphere, PKMNC, platform;

	// // pokemon
	// shared_ptr<Shape> MMK, PKCH, ZUBAT;

	// // wind turbine pieces
	// shared_ptr<Shape> WTStick, WTEng, WTSpin, WTBlade, WTFoundation;

	// // plant
	// shared_ptr<Shape> P1;

	Node * playerA1 = nullptr;
	Node * playerA2 = nullptr;
	Node * playerB1 = nullptr;
	Node * playerB2 = nullptr;

	// Contains vertex information for OpenGL
	GLuint VertexArrayID;

	// Data necessary to give our triangle to OpenGL
	GLuint VertexBufferID;

	float lightTrans = 0;
	float gRot = 0;
	float gTrans = 0;

	bool animate = false;
	float animRot = 0;
	int colorMode = 0;

	bool turn = true;

	float x = 0, y = 0, z = 0;


	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if(key == GLFW_KEY_W && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(1, playerA1);
				curr = playerA1;
				printMap();
				nodeDataPrintout(playerA1);
			} else {
				playerB1 = moveHelperRET(1, playerB1);
				curr = playerB1;
				printMap();
				nodeDataPrintout(playerB1);
			}
		}
		if(key == GLFW_KEY_A && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(3, playerA1);
				curr = playerA1;
				printMap();
				nodeDataPrintout(playerA1);
			} else {
				playerB1 = moveHelperRET(3, playerB1);
				curr = playerB1;
				printMap();
				nodeDataPrintout(playerB1);
			}
		}
		if(key == GLFW_KEY_S && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(2, playerA1);
				curr = playerA1;
				printMap();
				nodeDataPrintout(playerA1);
			} else {
				playerB1 = moveHelperRET(2, playerB1);
				curr = playerB1;
				printMap();
				nodeDataPrintout(playerB1);
			}
		}
		if(key == GLFW_KEY_D && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(4, playerA1);
				curr = playerA1;
				printMap();
				nodeDataPrintout(playerA1);
			} else {
				playerB1 = moveHelperRET(4, playerB1);
				curr = playerB1;
				printMap();
				nodeDataPrintout(playerB1);
			}
		}


		if(key == GLFW_KEY_O && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(5, playerA1);
				printMap();
				nodeDataPrintout(playerA1);
			} else {
				playerB1 = moveHelperRET(5, playerB1);
				printMap();
				nodeDataPrintout(playerB1);
			}
		}
		if(key == GLFW_KEY_P && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(6, playerA1);
				curr = playerA1;
				printMap();
				nodeDataPrintout(playerA1);
			} else {
				playerB1 = moveHelperRET(6, playerB1);
				curr = playerB1;
				printMap();
				nodeDataPrintout(playerB1);
			}
		}

		if(key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
			turn = !turn;
			curr = turn ? playerA1 : playerB1;
			cout << "\033[2J\033[1;1H";
			printMap();
			nodeDataPrintout(turn ? playerA1 : playerB1);
		}


		
		if(key == GLFW_KEY_G && action == GLFW_RELEASE) {
			++x;
		}
		if(key == GLFW_KEY_B && action == GLFW_RELEASE) {
			--x;
		}

		
		if(key == GLFW_KEY_H && action == GLFW_RELEASE) {
			++y;
		}
		if(key == GLFW_KEY_N && action == GLFW_RELEASE) {
			--y;
		}
		
		if(key == GLFW_KEY_J && action == GLFW_RELEASE) {
			++z;
		}
		if(key == GLFW_KEY_M && action == GLFW_RELEASE) {
			--z;
		}

		if(key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
			cout << "x is: " << x << endl; 
			cout << "y is: " << y << endl; 
			cout << "z is: " << z << endl; 
		}

		if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}
		if (key == GLFW_KEY_0 && action == GLFW_RELEASE) {
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
	}

	void mouseCallback(GLFWwindow *window, int button, int action, int mods)
	{
		double posX, posY;

		if (action == GLFW_PRESS)
		{
			 glfwGetCursorPos(window, &posX, &posY);
			 cout << "Pos X " << posX <<  " Pos Y " << posY << endl;
		}
	}

	void resizeCallback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void init(const std::string& resourceDirectory)
	{
		GLSL::checkVersion();

		// Set background color.
		glClearColor(0.90f, .53f, .49f, 0.81f); // 135, 125, 206
		// Enable z-buffer test.
		glEnable(GL_DEPTH_TEST);

		// Initialize the GLSL program.
		prog = make_shared<Program>();
		prog->setVerbose(true);
		prog->setShaderNames(resourceDirectory + "/simple_vert.glsl", resourceDirectory + "/simple_frag.glsl");
		prog->init();
		prog->addUniform("P");
		prog->addUniform("V");
		prog->addUniform("M");
		prog->addUniform("MatAmb");

		prog->addUniform("LightDir");
		prog->addUniform("bendAmount");
		prog->addUniform("colorMode");
		
		prog->addUniform("lightP");
		prog->addAttribute("vertPos");
		prog->addAttribute("vertNor");
		prog->addAttribute("vertTex");

		nodePopulation();

		playerA1 = topLeft;
		playerB1 = bottomRight;
		
		cout << "\033[2J\033[1;1H";
		curr = turn ? playerA1 : playerB1;
		printMap();
		nodeDataPrintout(turn ? playerA1 : playerB1);
		// nodeDataPrintout(playerA1);
		// nodeDataPrintout(playerB1);
	}

	// changed into a helper function to help loading all the objects used in the program
	void initGeom(const std::string& objectDirectory, string obj, shared_ptr<Shape> & sh)
	{
		sh = make_shared<Shape>();
		sh->loadMesh(objectDirectory + obj);
		sh->resize();
		sh->init();
	}

	// loads all objects and stores them in their respective shared_ptr<Shape> handles
	void initObjects(const std::string & objDir) {
		// initGeom(objDir, "/SmoothSphere.obj", SmoothSphere);
		// initGeom(objDir, "/PC/pokemoncenter.obj", PKMNC);
		// initGeom(objDir, "/PC/platform.obj", platform);
		// initGeom(objDir, "/PKMN/MMK.obj", MMK);
		// initGeom(objDir, "/PKMN/PKCH.obj", PKCH);
		// initGeom(objDir, "/PKMN/ZUBAT.obj", ZUBAT);
		// initGeom(objDir, "/wt/WTStick.obj", WTStick);
		// initGeom(objDir, "/wt/WTEng.obj", WTEng);
		// initGeom(objDir, "/wt/WTSpin.obj", WTSpin);
		// initGeom(objDir, "/wt/WTBlade.obj", WTBlade);
		// initGeom(objDir, "/wt/WTFoundation.obj", WTFoundation);
		// initGeom(objDir, "/plants/plant1.obj", P1);
		initGeom(objDir, "/cube.obj", cube);
		
	}

	void SetMaterial(int i) {
		prog->bind();
		switch (i) {
    		case 0: //green
    			glUniform3f(prog->getUniform("MatAmb"), 0.00, 0.70, 0.50);
    			break;
    		case 1: // flat grey
    			glUniform3f(prog->getUniform("MatAmb"), 0.13, 0.13, 0.13);
    			break;
    		case 2: //yellow
    			glUniform3f(prog->getUniform("MatAmb"), 0.90, 0.90, 0.00);
    			break;
			case 3: //red
				glUniform3f(prog->getUniform("MatAmb"), 0.90, 0.00, 0.00);
				break;
			case 4: //dark green
				glUniform3f(prog->getUniform("MatAmb"), 0.10, 0.30, 0.10);
				break;
			case 5: //light gray 1
				glUniform3f(prog->getUniform("MatAmb"), 0.3, 0.3, 0.3);
				break;
			case 6: //light gray 2
				glUniform3f(prog->getUniform("MatAmb"), 0.45, 0.45, 0.45);
				break;
			case 7: // dark green
				glUniform3f(prog->getUniform("MatAmb"), 0.00, 0.35, 0.20);
				break;
			case 8: // blue
				glUniform3f(prog->getUniform("MatAmb"), 0.09, 0.38, 0.56);
				break;
			case 9: // gray-yellow
    			glUniform3f(prog->getUniform("MatAmb"), 0.40, 0.45, 0.30);
			case 10:
    			glUniform3f(prog->getUniform("MatAmb"), 1, 1, 1);
			case 11:
    			glUniform3f(prog->getUniform("MatAmb"), 0, 0, 0);

  		}
	}


	void render()
	{
		// Get current frame buffer size.
		int width, height;
		glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
		glViewport(0, 0, width, height);

		// Clear framebuffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use the matrix stack for Lab 6
		float aspect = width/(float)height;

		// Create the matrix stacks - please leave these alone for now
		auto Projection = make_shared<MatrixStack>();
		auto View = make_shared<MatrixStack>();
		auto Model = make_shared<MatrixStack>();

		// Apply perspective projection.
		Projection->pushMatrix();
		Projection->perspective(45.0f, aspect, 0.01f, 100.0f);

		// View is identity - for now
		View->pushMatrix();
		// View->print();

		// Draw a stack of cubes with indiviudal transforms
		prog->bind();
		glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(Projection->topMatrix()));
		glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, value_ptr(View->topMatrix()));

		glUniform3f(prog->getUniform("LightDir"), 2, 1.5, 0);	// used for shading in one mode
		glUniform1i(prog->getUniform("colorMode"), colorMode);	// used to switch colors around 
		
		glUniform3f(prog->getUniform("lightP"), 1, 1, 1);
		// glUniform3f(prog->getUniform("lightP"), lightTrans+2, 3, 4);

		// if (animate) animRot += 0.025;

		Model->pushMatrix();
			Model->rotate(gRot, vec3(0, 1, 0));

		Model->pushMatrix();
			Model->rotate(gRot, vec3(0, 1, 0));
			shape = cube;
			for (int i = 0; i < 8+x; i++) {
				for (int j = 0; j < 8+y; j++) {
					Model->pushMatrix();
						Model->translate(vec3((-2.625+(2.0/(2.678125))*(7-i)), -2+y, -5+gTrans-((2.0/(2.678125))*(8-j))));
						// Model->translate(vec3((-3+(2.0/(2.678125))*i), -2+y, -5+gTrans+(j*(-1+z))));
						Model->scale(vec3(0.375, 0.025, 0.375));
						SetMaterial((10+(i+j))%2);
						glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(Model->topMatrix()));
						shape->draw(prog);
					Model->popMatrix();
				}
			}
		Model->popMatrix();

		// cout << "\033[2J\033[1;1H";
		// printMap();
		// nodeDataPrintout(turn ? playerA1 : playerB1);

		Model->popMatrix();

		prog->unbind();

		// Pop matrix stacks.
		Projection->popMatrix();
		View->popMatrix();

	}
};




































int main(int argc, char ** argv) {

	Application *application = new Application();
	
	WindowManager *windowManager = new WindowManager();
	windowManager->init(1280, 800);
	windowManager->setEventCallbacks(application);
	application->windowManager = windowManager;
	
	application->init("../resources");
	application->initObjects("../resources");

	cout << "\033[2J\033[1;1H";

	// Loop until the user closes the window.
	while (! glfwWindowShouldClose(windowManager->getHandle()))
	{
		// Render scene.
		application->render();

		// Swap front and back buffers.
		glfwSwapBuffers(windowManager->getHandle());
		// Poll for and process events.
		glfwPollEvents();
	}

	// Quit program.
	windowManager->shutdown();

	return 0;
}