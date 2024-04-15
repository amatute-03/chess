#include <iostream>
#include <glad/glad.h>

#include "GLSL.h"
#include "Program.h"
#include "Shape.h"
#include "MatrixStack.h"
#include "WindowManager.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include <thread>
#include <stdio.h>
#include "piece.h"


#define PI 3.14159265359

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

extern "C" {
    void printMap();
    void nodePopulation();
    void usePiece(Node* node);
	void nodeCreation();
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

bool turn = true;

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
void setCURR(Node* n) {
	curr = n;
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

void nodeCreation() {
	Node* temp = new Node;
	temp->landingSpot = false;

	BISA = ((BISA == 0) ? ((++BISB % 8 == 1) ? BISA : ++BISA) : ((++BISB % 8 == 1) ? BISA : --BISA));
	temp->info = checks[BISA];

	if(row < 2  || row > 5) {
		temp->piecePresent = true;
		temp->pieceHeld->setPieceType(sym[PieceSetUp]);
		temp->pieceHeld->setMoveType(pieceTypes[PieceSetUp++]);
		temp->pieceHeld->setSide(row < 2 ? 1 : 0);
	} 
	else {
		temp->piecePresent = false;
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
}

void nodePopulation() {
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			nodeCreation();
		}
	}
}

void usePiece(Node* node) {
	node->piecePresent = true;
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
				if(selected == NULL && n->piecePresent && (n->pieceHeld->getSide() == turn)) {
					selected = n;
				}
				else if(selected != NULL && n == selected) {
					selected = NULL;
				}
				else if(selected != NULL && n->landingSpot) {
					movedPiece();
					selected = NULL;
					turn = !turn;
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


string getPieceShape(int i, int j) {
	string out = "     ";
	Node * helper = topLeft;
	for(int a = 0; a < i; ++a) {
		helper = helper->right;
	}
	for(int b = 0; b < j; ++b) {
		helper = helper->down;
	}

	if(helper == curr) {
		out[2] = char(1);
	} else {
		out[2] = char(0);
	}

	if(helper == selected) {
		out[3] = char(1);
	} else {
		out[3] = char(0);
	}

	if(inPath(helper)) {
		out[4] = char(1);
	} else {
		out[4] = char(0);
	}

	if (helper->piecePresent == 0) {
		out[0] = char(6);
		out[1] = char(0);
		return out;
	}
	out[0] = char(helper->pieceHeld->getMoveVal());
	out[1] = char(helper->pieceHeld->getSide());
	return out;
}


class Application : public EventCallbacks
{

public:

	WindowManager * windowManager = nullptr;

	// Our shader program
	std::shared_ptr<Program> prog;

	// Shape to be used (from obj file)
	shared_ptr<Shape> shape;
	shared_ptr<Shape> pawn, rook, knight, bishop, king, queen;
	shared_ptr<Shape> cube, SmoothSphere;

	Node * playerA = nullptr;
	Node * playerB = nullptr;

	// Contains vertex information for OpenGL
	GLuint VertexArrayID;

	// Data necessary to give our triangle to OpenGL
	GLuint VertexBufferID;

	float lightTrans = 0;
	float gRot = 0;
	float gTrans = 0;

	bool animate = false;
	float animRot = 0;
	int colorMode = 1;
	bool turnAnimation = false;
	float turnSwitchAnimation = 0;


	float x = 0, y = 0, z = 0, l = 0, m = 0, o = 0, p = 0;

	void moveAction(int n) {
		cout << "\033[2J\033[1;1H";
		(turn ? playerA : playerB) = moveHelperRET(n, (turn ? playerA : playerB));
		curr = (turn ? playerA : playerB);
		printMap();
	}


	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if(key == GLFW_KEY_W && action == GLFW_RELEASE) {
			if(!turnAnimation) {
				if (turn) {
					moveAction(2);	// down
				} else {
					moveAction(1);	// up
				}
			}
		}
		if(key == GLFW_KEY_A && action == GLFW_RELEASE) {
			if(!turnAnimation) {
				if (turn) {
					moveAction(4);	// right
				} else {
					moveAction(3);	// left
				}
			}
		}
		if(key == GLFW_KEY_S && action == GLFW_RELEASE) {
			if(!turnAnimation) {
				if (turn) {
					moveAction(1);	// up
				} else {
					moveAction(2);	// down
				}
			}
		}
		if(key == GLFW_KEY_D && action == GLFW_RELEASE) {
			if(!turnAnimation) {
				if (turn) {
					moveAction(3);	// left
				} else {
					moveAction(4);	// right
				}
			}
		}


		if(key == GLFW_KEY_O && action == GLFW_RELEASE) { // choice
			
			cout << "\033[2J\033[1;1H";
			bool swap = turn;
			
			if(turn) {
				playerA = moveHelperRET(5, playerA);
			} else {
				playerB = moveHelperRET(5, playerB);
			}
			
			curr = turn ? playerA : playerB;
			printMap();

			if(swap != turn) turnAnimation = true;
		}
		if(key == GLFW_KEY_P && action == GLFW_RELEASE) { // release
			moveAction(6);
		}



		if(key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
			turn = !turn;
			turnAnimation = true;
			curr = turn ? playerA : playerB;
			cout << "\033[2J\033[1;1H";
			printMap();
		}

		if(key == GLFW_KEY_0 && action == GLFW_RELEASE) {
			colorMode = colorMode < 1 ? ++colorMode : 0;
		}

		if(key == GLFW_KEY_2 && action == GLFW_RELEASE) {
			turnAnimation = !turnAnimation;
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


		if(key == GLFW_KEY_K && action == GLFW_RELEASE) {
			++l;
		}
		if(key == GLFW_KEY_COMMA && action == GLFW_RELEASE) {
			--l;
		}
		if(key == GLFW_KEY_L && action == GLFW_RELEASE) {
			++m;
		}
		if(key == GLFW_KEY_PERIOD && action == GLFW_RELEASE) {
			--m;
		}
		if(key == GLFW_KEY_SEMICOLON && action == GLFW_RELEASE) {
			++o;
		}
		if(key == GLFW_KEY_SLASH && action == GLFW_RELEASE) {
			--o;
		}
		if(key == GLFW_KEY_LEFT_BRACKET && action == GLFW_RELEASE) {
			++p;
		}
		if(key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_RELEASE) {
			--p;
		}
		if(key == GLFW_KEY_0 && action == GLFW_RELEASE) {
			x = y = z = l = m = o = p = 0;
		}
		if(key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
			cout << "x is: " << x << endl; 
			cout << "y is: " << y << endl; 
			cout << "z is: " << z << endl; 
			cout << "l is: " << l << endl; 
			cout << "m is: " << m << endl; 
			cout << "o is: " << o << endl; 
			cout << "p is: " << p << endl; 
		}

		if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}
		if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
		if(key == GLFW_KEY_1 && action == GLFW_RELEASE) {
			animate = !animate;
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
		glClearColor(0.90f, .53f, .49f, 0.81f);
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

		playerA = getTL();
		playerB = getBR();
		
		cout << "\033[2J\033[1;1H";
		setCURR(turn ? playerA : playerB);
		printMap();
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
		initGeom(objDir, "/cube.obj", cube);
		initGeom(objDir, "/pawn.obj", pawn);
		initGeom(objDir, "/rook.obj", rook);
		initGeom(objDir, "/knight.obj", knight);
		initGeom(objDir, "/bishop.obj", bishop);
		initGeom(objDir, "/king.obj", king);
		initGeom(objDir, "/queen.obj", queen);
		initGeom(objDir, "/SmoothSphere.obj", SmoothSphere);
		
	}

	void setShape(int n) {
		switch (n){
			case 0:
				shape = pawn;
				break;
			case 1:
				shape = rook;
				break;
			case 2:
				shape = knight;
				break;
			case 3:
				shape = bishop;
				break;
			case 4:
				shape = queen;
				break;
			case 5:
				shape = king;
				break;
			case 6:
				shape = cube;
				break;
		};
	}

	void SetMaterial(int i) {
		prog->bind();
		switch (i) {
			case 0: // white
    			glUniform3f(prog->getUniform("MatAmb"), 1, 1, 1);
				break;
			case 1: // black
    			glUniform3f(prog->getUniform("MatAmb"), 0, 0, 0);
				break;
			case 2: // player2 color
				glUniform3f(prog->getUniform("MatAmb"), 0.09, 0.38, 0.56);
				break;
			case 3: // player1 color
				glUniform3f(prog->getUniform("MatAmb"), 0.25, 0.05, 0.40);
				break;
			case 4: // gray 1
				glUniform3f(prog->getUniform("MatAmb"), 0.45, 0.45, 0.45);
				break;
			case 5: // gray 2
				glUniform3f(prog->getUniform("MatAmb"), 0.3, 0.3, 0.3);
				break;
			case 6: // yellow for selected spot when not current spot
				glUniform3f(prog->getUniform("MatAmb"), 1, 1, 0);
				break;
			case 7:	// green for current spot chosen to move to
				glUniform3f(prog->getUniform("MatAmb"), 0, 1, 0);
				break;
			case 8: // cyan for current spot when selected
				glUniform3f(prog->getUniform("MatAmb"), 0, 1, 1);
				break;
			case 9: // magenta for possible options to choose from
				glUniform3f(prog->getUniform("MatAmb"), 1, 0, 1);
				break;
			case 10: // red for a bad move choice when selected
				glUniform3f(prog->getUniform("MatAmb"), 1, 0, 0);
				break;
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

		// makes view face down like person looking at board
		View->rotate(PI/(0.12), vec3(1, 0, 0));
		View->translate(vec3(0, -6, 0));

		// causes the view to rotate around the board after a turn swap is caused
		View->rotate(PI*(1+turnSwitchAnimation), vec3(0, 1, 0));
		View->translate(vec3(4*cos(PI*(1+turnSwitchAnimation-0.5)), 0, 4*sin(PI*(1+turnSwitchAnimation-0.5))));

		if(turnAnimation) {
			turnSwitchAnimation += 0.01;
			if((fabs(turnSwitchAnimation - 1.0) < 0.001)) {
				turnAnimation = !turnAnimation;
			}
			else if(fabs(turnSwitchAnimation - 2.0) < 0.001) {
				turnAnimation = !turnAnimation;
				turnSwitchAnimation = 0;
			}

		}



		View->translate(vec3(0.0115, 1, 8.353));

		// Draw a stack of cubes with indiviudal transforms
		prog->bind();
		glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(Projection->topMatrix()));
		glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, value_ptr(View->topMatrix()));

		glUniform3f(prog->getUniform("LightDir"), 6, 2, -1);	// used for shading in one mode
		// glUniform3f(prog->getUniform("LightDir"), 6+x, 2+y, -1+z);	// used for shading in one mode
		// glUniform3f(prog->getUniform("LightDir"), 2+x, -6+y, z);	// used for shading in one mode
		// glUniform3f(prog->getUniform("LightDir"), 2, 1.5, 0);	// used for shading in one mode
		glUniform1i(prog->getUniform("colorMode"), colorMode);	// used to switch colors around 
		
		glUniform3f(prog->getUniform("lightP"), 2, 0, 3);
		// glUniform3f(prog->getUniform("lightP"), 2+x, 0+y, 3+z);
		// glUniform3f(prog->getUniform("lightP"), lightTrans+2, 3, 4);


		// if (animate) animRot += 0.005;
		// if (animate) animRot += 0.025;

		Model->pushMatrix();
			Model->rotate(gRot, vec3(0, 1, 0));

			Model->pushMatrix();
				Model->rotate(gRot, vec3(0, 1, 0));
				shape = cube;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						string Val0Sid1Cur2Sel3Pat4 = getPieceShape(i, j);

						Model->pushMatrix();
							Model->translate(vec3((-2.625+(2.0/(2.678125))*i), -2, -5+gTrans-((2.0/(2.678125))*(8-j))));
							Model->scale(vec3(0.375, 0.025, 0.375));
							if (Val0Sid1Cur2Sel3Pat4[2] && Val0Sid1Cur2Sel3Pat4[3]) SetMaterial(8);
							else if (Val0Sid1Cur2Sel3Pat4[4] && Val0Sid1Cur2Sel3Pat4[2]) SetMaterial(7);
							else if (Val0Sid1Cur2Sel3Pat4[4]) SetMaterial(9);
							else if (Val0Sid1Cur2Sel3Pat4[3]) SetMaterial(6);
							else if (Val0Sid1Cur2Sel3Pat4[2] && !getSEL()) SetMaterial(8);
							else if (Val0Sid1Cur2Sel3Pat4[2]) SetMaterial(10);
							else SetMaterial(((i+j)%2));

							glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(Model->topMatrix()));
							shape->draw(prog);

							Model->pushMatrix();
								if (Val0Sid1Cur2Sel3Pat4[0] < 6) {
									setShape(Val0Sid1Cur2Sel3Pat4[0]);
									Model->translate(vec3(0, 15, 0));
									if(Val0Sid1Cur2Sel3Pat4[2] || Val0Sid1Cur2Sel3Pat4[3]) {
										Model->translate(vec3(0, 30, 0));
									}
									if(shape != pawn && shape != rook) {
										Model->scale(vec3(1.25, 1.25, 1.25));
										Model->translate(vec3(0, 2, 0));
									}
									Model->scale(vec3(1, 15, 1));
									if(Val0Sid1Cur2Sel3Pat4[1]) {
										Model->rotate(3, vec3(0, 30, 0));		// rotates opposing side to face right direction
									}
									Model->rotate(-1.6, vec3(1, 0, 0));
									SetMaterial(2 + int(Val0Sid1Cur2Sel3Pat4[1]) + 2*Val0Sid1Cur2Sel3Pat4[2]);
									glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(Model->topMatrix()));
									shape->draw(prog);
								}

								if(getSEL() && Val0Sid1Cur2Sel3Pat4[2]) {
									setShape(getSEL()->pieceHeld->getMoveVal());
									if (Val0Sid1Cur2Sel3Pat4[0] < 6) {
										Model->translate(vec3(0, 0, 4));
									} else {
										Model->scale(vec3(1, 15, 1));
										Model->translate(vec3(0, 6, 0));
										Model->rotate(-2, vec3(1, 0, 0));
										Model->rotate(0.4, vec3(1, 0, 0));
									}
									Model->scale(vec3(0.6, 0.6, 0.6));
									if (Val0Sid1Cur2Sel3Pat4[4]) SetMaterial(7);
									else if (Val0Sid1Cur2Sel3Pat4[3] && Val0Sid1Cur2Sel3Pat4[2]) SetMaterial(6);
									else SetMaterial(10);
									glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(Model->topMatrix()));
									shape->draw(prog);
								}
								setShape(6);
								
							Model->popMatrix();
						Model->popMatrix();
					}
				}
			Model->popMatrix();

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
	windowManager->init(800, 800);
	// windowManager->init(1280, 800);
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