
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

extern "C" {
    void printMap();
    void nodePopulation();
    void usePiece(Node* node);
	void nodeCreation();
	// Node* nodeCreation();
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
// Node* nodeCreation() {
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

	// return temp;
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
	string out = "  ";
	Node * helper = topLeft;
	for(int a = 0; a < i; ++a) {
		helper = helper->right;
	}
	for(int b = 0; b < j; ++b) {
		helper = helper->down;
	}
	if (helper->piecePresent == 0) {
		out[0] = '6';
		out[1] = '0';
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
	shared_ptr<Shape> cube;

	Node * playerA1 = nullptr;
	// Node * playerA2 = nullptr;
	Node * playerB1 = nullptr;
	// Node * playerB2 = nullptr;

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


	float x = 0, y = 0, z = 0, l = 0, m = 0, o = 0, p = 0;


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
			} else {
				playerB1 = moveHelperRET(1, playerB1);
				curr = playerB1;
				printMap();
			}
		}
		if(key == GLFW_KEY_A && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(3, playerA1);
				curr = playerA1;
				printMap();
			} else {
				playerB1 = moveHelperRET(3, playerB1);
				curr = playerB1;
				printMap();
			}
		}
		if(key == GLFW_KEY_S && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(2, playerA1);
				curr = playerA1;
				printMap();
			} else {
				playerB1 = moveHelperRET(2, playerB1);
				curr = playerB1;
				printMap();
			}
		}
		if(key == GLFW_KEY_D && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(4, playerA1);
				curr = playerA1;
				printMap();
			} else {
				playerB1 = moveHelperRET(4, playerB1);
				curr = playerB1;
				printMap();
			}
		}


		if(key == GLFW_KEY_O && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(5, playerA1);
				curr = turn ? playerA1 : playerB1;
				printMap();
			} else {
				playerB1 = moveHelperRET(5, playerB1);
				curr = turn ? playerA1 : playerB1;
				printMap();
			}
		}
		if(key == GLFW_KEY_P && action == GLFW_RELEASE) {
			cout << "\033[2J\033[1;1H";
			if(turn) {
				playerA1 = moveHelperRET(6, playerA1);
				curr = playerA1;
				printMap();
			} else {
				playerB1 = moveHelperRET(6, playerB1);
				curr = playerB1;
				printMap();
			}
		}

		if(key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
			turn = !turn;
			curr = turn ? playerA1 : playerB1;
			cout << "\033[2J\033[1;1H";
			printMap();
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
		if(key == GLFW_KEY_BACKSLASH && action == GLFW_RELEASE) {
			--o;
		}
		if(key == GLFW_KEY_LEFT_BRACKET && action == GLFW_RELEASE) {
			++p;
		}
		if(key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_RELEASE) {
			--p;
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

		playerA1 = getTL();
		playerB1 = getBR();
		
		cout << "\033[2J\033[1;1H";
		curr = turn ? playerA1 : playerB1;
		printMap();
		// nodeDataPrintout(turn ? playerA1 : playerB1);
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
		initGeom(objDir, "/cube.obj", cube);
		initGeom(objDir, "/pawn.obj", pawn);
		initGeom(objDir, "/rook.obj", rook);
		initGeom(objDir, "/knight.obj", knight);
		initGeom(objDir, "/bishop.obj", bishop);
		initGeom(objDir, "/king.obj", king);
		initGeom(objDir, "/queen.obj", queen);
		
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
			case 10: // white
    			glUniform3f(prog->getUniform("MatAmb"), 1, 1, 1);
			case 11: // black
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
		View->rotate(-1, vec3(-1, 0, 0));
		// View->rotate(-1+p, vec3(-1+l, m, o));
		View->translate(vec3(0, -5, 4));
		// View->translate(vec3(x, -5+y, 4+z));

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
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						Model->pushMatrix();
							Model->translate(vec3((-2.625+(2.0/(2.678125))*i), -2, -5+gTrans-((2.0/(2.678125))*(8-j))));
							Model->scale(vec3(0.375, 0.025, 0.375));
							SetMaterial((10+(i+j))%2);
							glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(Model->topMatrix()));
							shape->draw(prog);

							Model->pushMatrix();
								string hold = getPieceShape(i, j);
								switch (hold[0]){
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
								if (shape != cube) {
									Model->translate(vec3(0, 15, 0));
									Model->scale(vec3(1, 15, 1));
									if(hold[1]) {
										Model->rotate(3, vec3(0, 30, -10));
									}
									Model->rotate(-2, vec3(1, 0, 0));
									SetMaterial(int(hold[1])+3);
									glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(Model->topMatrix()));
									shape->draw(prog);
									shape = cube;
								}
								
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
	windowManager->init(600, 600);
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