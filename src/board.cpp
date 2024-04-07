
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
	cin >> movement;
	// if (argCount != 1) {string h = arguments[ccc++];movement = int(h.at(0)-48);} else {cin >> movement;}
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


























class Application : public EventCallbacks
{

public:

	WindowManager * windowManager = nullptr;

	// Our shader program
	std::shared_ptr<Program> prog;

	// Shape to be used (from obj file)
	shared_ptr<Shape> shape;

	// location
	shared_ptr<Shape> SmoothSphere, PKMNC, platform;

	// pokemon
	shared_ptr<Shape> MMK, PKCH, ZUBAT;

	// wind turbine pieces
	shared_ptr<Shape> WTStick, WTEng, WTSpin, WTBlade, WTFoundation;

	// plant
	shared_ptr<Shape> P1;

	Node * playerA1, playerA2, playerB1, playerB2;

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

	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		// if(key = GLFW_KEY_W && action == GLFW_RELEASE) {
		// 	if(turn) {
				
		// 	} else {
				
		// 	}
		// }
		// if(key = GLFW_KEY_A && action == GLFW_RELEASE) {
		// 	if(turn) {

		// 	} else {
				
		// 	}
		// }
		// if(key = GLFW_KEY_S && action == GLFW_RELEASE) {
		// 	if(turn) {

		// 	} else {
				
		// 	}
		// }
		// if(key = GLFW_KEY_D && action == GLFW_RELEASE) {
		// 	if(turn) {

		// 	} else {
				
		// 	}
		// }

		if(key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
			turn = !turn;
			cout << turn << endl;
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
		glClearColor(0.90f, .62f, .0f, 1.0f);
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
		initGeom(objDir, "/SmoothSphere.obj", SmoothSphere);
		initGeom(objDir, "/PC/pokemoncenter.obj", PKMNC);
		initGeom(objDir, "/PC/platform.obj", platform);
		initGeom(objDir, "/PKMN/MMK.obj", MMK);
		initGeom(objDir, "/PKMN/PKCH.obj", PKCH);
		initGeom(objDir, "/PKMN/ZUBAT.obj", ZUBAT);
		initGeom(objDir, "/wt/WTStick.obj", WTStick);
		initGeom(objDir, "/wt/WTEng.obj", WTEng);
		initGeom(objDir, "/wt/WTSpin.obj", WTSpin);
		initGeom(objDir, "/wt/WTBlade.obj", WTBlade);
		initGeom(objDir, "/wt/WTFoundation.obj", WTFoundation);
		initGeom(objDir, "/plants/plant1.obj", P1);

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
  		}
	}



	void loadWT(shared_ptr<MatrixStack> mod, float a1, float a2, float a3, float a4, float a5) {
		mod->pushMatrix();
			mod->rotate(1, vec3(1, 0, 1));

			// turbine stick
			mod->pushMatrix();
				shape = WTStick;
				mod->translate(vec3(0, a5, 0));
				mod->scale(vec3(0.15, 0.15, 0.15));
				mod->rotate(a1, vec3(a2, a3, a4));
				SetMaterial(5);
				glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
				shape->draw(prog);

				// top block piece
				mod->pushMatrix();
					shape = WTEng;
					mod->translate(vec3(-0.05, 1.1, 0));
					mod->scale(vec3(0.25, 0.25, 0.25));
					mod->rotate(-1.5 + cos(animRot/2)/5, vec3(0, 1, 0));
					SetMaterial(5);
					glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
					shape->draw(prog);

					// blade turning piece
					mod->pushMatrix();
						shape = WTSpin;
						mod->translate(vec3(1.3, 0, 0));
						mod->rotate(-animRot, vec3(1, 0, 0));
						mod->scale(vec3(0.3, 0.3, 0.3));
						SetMaterial(6);
						glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
						shape->draw(prog);

						mod->pushMatrix();
							shape = WTBlade;
							mod->translate(vec3(-0.4, 2.75, -1.3));
							mod->scale(vec3(13, 13, 13));
							SetMaterial(1);
							glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
							shape->draw(prog);
						mod->popMatrix();
					mod->popMatrix();
				mod->popMatrix();

				// base plate
				mod->pushMatrix();
					shape = WTFoundation;
					mod->translate(vec3(0, -1.05, 0));
					mod->scale(vec3(0.25, 0.25, 0.25));
					SetMaterial(1);
					glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
					shape->draw(prog);
				mod->popMatrix();
			mod->popMatrix();
		mod->popMatrix();
	}

	void loadPKMNC(shared_ptr<MatrixStack> mod) {
		mod->pushMatrix();
			mod->rotate(0.75, vec3(2.05, 3.4, 3.45));
			shape = PKMNC;
			mod->translate(vec3(0, 1.175, 0));
			mod->scale(vec3(0.35, 0.35, 0.35));
			mod->rotate(1.7, vec3(0, 1, 0));
			SetMaterial(3);
			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
			shape->draw(prog);

			mod->pushMatrix();
				shape = platform;
				mod->translate(vec3(0, -0.725, 0));
				mod->scale(vec3(0.82, 8.6, 2.3));
				SetMaterial(1);
				glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
				shape->draw(prog);
			mod->popMatrix();
		mod->popMatrix();
	}

	void loadPKMN(shared_ptr<MatrixStack> mod) {

		// loads pikachu
		mod->pushMatrix();
			mod->rotate(0.95, vec3(9.15, 3.85, 3.4));
			shape = PKCH;
			mod->rotate(3+animRot/5, vec3(0, 11, 1));
			mod->translate(vec3(-0.05, 1.15+((sin(animRot)+1)/(15)), 0));
			mod->scale(vec3(0.15, 0.15, 0.15));
			mod->rotate(6, vec3(0, 1, 0));
			SetMaterial(2);
			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
			shape->draw(prog);
		mod->popMatrix();

		// loads Mimikyu
		mod->pushMatrix();
			mod->rotate(0.95, vec3(9.15, 3.85, 3.4));
			shape = MMK;
			mod->rotate(animRot/5, vec3(0, 11, 1));
			mod->translate(vec3(-0.05, 1.15+((cos(animRot)+1)/(15)), 0));
			mod->scale(vec3(0.15, 0.15, 0.15));
			mod->rotate(4.3, vec3(0, 1, 0));
			SetMaterial(9);
			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
			shape->draw(prog);
		mod->popMatrix();

		// loads zubats
		glUniform1f(prog->getUniform("bendAmount"), ((0.9*cos(animRot/(-0.7)))/(1.3)));
		for(int i = 0; i < 9; i+=4) {
			mod->pushMatrix();
				mod->rotate(1, vec3(0.1, 0.1, -0.1));
				shape = ZUBAT;
				mod->rotate(i+animRot/5, vec3(0.2, -0.5, 0.2));
				mod->translate(vec3(0, 1.5, 0));
				mod->scale(vec3(0.1, 0.1, 0.1));
				mod->rotate(1, vec3(1, 0, 0));
				mod->rotate(0.4, vec3(0, 1, 0));
				mod->rotate(0.5, vec3(0, 0, 1));
				SetMaterial(8);
				glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
				shape->draw(prog);
			mod->popMatrix();
		}
		glUniform1f(prog->getUniform("bendAmount"), 0);
	}

	void loadPlant(shared_ptr<MatrixStack> mod, float a1, float a2, float a3, float a4) {
		mod->pushMatrix();
			mod->rotate(a1, vec3(a2, a3, a4));
			mod->pushMatrix();
				shape = P1;
				mod->translate(vec3(0, 1.03, 0));
				mod->scale(vec3(0.05, 0.05, 0.05));
				SetMaterial(7);
				glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
				shape->draw(prog);
			mod->popMatrix();
		mod->popMatrix();
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
		
		glUniform3f(prog->getUniform("lightP"), lightTrans+2, 3, 4);

		// if (animate) animRot += 0.025;

		Model->pushMatrix();
			//global rotate (the whole scene)
			// Model->rotate(gRot, vec3(0, 1, 0));

			// // sphere center to place all other objects around
			// shape = SmoothSphere;
			// Model->translate(vec3(0, -5, -11 + gTrans));
			// Model->scale(vec3(5.7, 5.7, 5.7));
			// Model->rotate(-0.1 + sin(animRot/3)/10, vec3(0, 0, 1));
			// SetMaterial(0);
			// glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(Model->topMatrix()));
			// shape->draw(prog);

			// // loads wind turbine
			// loadWT(Model, 1, 0, 0.8, 0.05, 1.175);

			// // loads PMKN center
			// loadPKMNC(Model);

			// // loads PKMN
			// loadPKMN(Model);

			// // loads plants
			// Model->pushMatrix();
			// 	for(int j = 0; j < 17; ++j) {
			// 		for(int i = 1; i < 17; ++i) {
			// 			Model->rotate(j, vec3(0, 1, 0));
			// 			loadPlant(Model, (0.2)*i, (-0.95)*j, (2.45)*j, (5.3)*j);
			// 		}

			// 	}
			// Model->popMatrix();


		Model->popMatrix();

		prog->unbind();

		// Pop matrix stacks.
		Projection->popMatrix();
		View->popMatrix();

	}
};




































int main(int argc, char ** argv) {
	arguments = argv;
	argCount = argc;

	Application *application = new Application();
	
	WindowManager *windowManager = new WindowManager();
	windowManager->init(1280, 800);
	windowManager->setEventCallbacks(application);
	application->windowManager = windowManager;

	
	application->init("../resources");
	application->initObjects("../resources");

	cout << "\033[2J\033[1;1H";

	// nodePopulation();

	// movingAround(topLeft);

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