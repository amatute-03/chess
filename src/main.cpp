// /* Lab 6 base code - transforms using matrix stack built on glm
//  * CPE 471 Cal Poly Z. Wood + S. Sueda + I. Dunn
//  */

// #include <iostream>
// #include <glad/glad.h>

// #include "GLSL.h"
// #include "Program.h"
// #include "Shape.h"
// #include "MatrixStack.h"
// #include "WindowManager.h"

// // value_ptr for glm
// #include <glm/gtc/type_ptr.hpp>
// #include <glm/gtc/matrix_transform.hpp>

// using namespace std;
// using namespace glm;

// class Application : public EventCallbacks
// {

// public:

// 	WindowManager * windowManager = nullptr;

// 	// Our shader program
// 	std::shared_ptr<Program> prog;

// 	// Shape to be used (from obj file)
// 	shared_ptr<Shape> shape;

// 	// location
// 	shared_ptr<Shape> SmoothSphere, PKMNC, platform;

// 	// pokemon
// 	shared_ptr<Shape> MMK, PKCH, ZUBAT;

// 	// wind turbine pieces
// 	shared_ptr<Shape> WTStick, WTEng, WTSpin, WTBlade, WTFoundation;

// 	// plant
// 	shared_ptr<Shape> P1;


// 	// Contains vertex information for OpenGL
// 	GLuint VertexArrayID;

// 	// Data necessary to give our triangle to OpenGL
// 	GLuint VertexBufferID;

// 	float lightTrans = 0;
// 	float gRot = 0;
// 	float gTrans = 0;

// 	bool animate = false;
// 	float animRot = 0;
// 	int colorMode = 0;

// 	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
// 	{
// 		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
// 			glfwSetWindowShouldClose(window, GL_TRUE);
// 		}
// 		if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
// 			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
// 		}
// 		if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
// 			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
// 		}

// 		if ((key == GLFW_KEY_O) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT) || (action == GLFW_RELEASE))) {
// 			lightTrans--;
// 		}
// 		if ((key == GLFW_KEY_P) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT) || (action == GLFW_RELEASE))) {
// 			lightTrans++;
// 		}

// 		if ((key == GLFW_KEY_W) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT) || (action == GLFW_RELEASE))) {
// 			gTrans++;
// 		}
// 		if ((key == GLFW_KEY_A) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT) || (action == GLFW_RELEASE))) {
// 			gRot+= 0.16;
// 		}
// 		if ((key == GLFW_KEY_S) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT) || (action == GLFW_RELEASE))) {
// 			gTrans--;
// 		}
// 		if ((key == GLFW_KEY_D) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT) || (action == GLFW_RELEASE))) {
// 			gRot-= 0.16;
// 		}

// 		if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
// 			animate = !animate;
// 		}
// 		if(key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
// 			colorMode += colorMode ? -1 : 1;
// 		}
// 	}

// 	void mouseCallback(GLFWwindow *window, int button, int action, int mods)
// 	{
// 		double posX, posY;

// 		if (action == GLFW_PRESS)
// 		{
// 			 glfwGetCursorPos(window, &posX, &posY);
// 			 cout << "Pos X " << posX <<  " Pos Y " << posY << endl;
// 		}
// 	}

// 	void resizeCallback(GLFWwindow *window, int width, int height)
// 	{
// 		glViewport(0, 0, width, height);
// 	}

// 	void init(const std::string& resourceDirectory)
// 	{
// 		GLSL::checkVersion();

// 		// Set background color.
// 		glClearColor(0.90f, .62f, .0f, 1.0f);
// 		// Enable z-buffer test.
// 		glEnable(GL_DEPTH_TEST);

// 		// Initialize the GLSL program.
// 		prog = make_shared<Program>();
// 		prog->setVerbose(true);
// 		prog->setShaderNames(resourceDirectory + "/simple_vert.glsl", resourceDirectory + "/simple_frag.glsl");
// 		prog->init();
// 		prog->addUniform("P");
// 		prog->addUniform("V");
// 		prog->addUniform("M");
// 		prog->addUniform("MatAmb");

// 		prog->addUniform("LightDir");
// 		prog->addUniform("bendAmount");
// 		prog->addUniform("colorMode");
		
// 		prog->addUniform("lightP");
// 		prog->addAttribute("vertPos");
// 		prog->addAttribute("vertNor");
// 		prog->addAttribute("vertTex");
// 	}

// 	// changed into a helper function to help loading all the objects used in the program
// 	void initGeom(const std::string& objectDirectory, string obj, shared_ptr<Shape> & sh)
// 	{
// 		sh = make_shared<Shape>();
// 		sh->loadMesh(objectDirectory + obj);
// 		sh->resize();
// 		sh->init();
// 	}

// 	// loads all objects and stores them in their respective shared_ptr<Shape> handles
// 	void initObjects(const std::string & objDir) {
// 		initGeom(objDir, "/SmoothSphere.obj", SmoothSphere);
// 		initGeom(objDir, "/PC/pokemoncenter.obj", PKMNC);
// 		initGeom(objDir, "/PC/platform.obj", platform);
// 		initGeom(objDir, "/PKMN/MMK.obj", MMK);
// 		initGeom(objDir, "/PKMN/PKCH.obj", PKCH);
// 		initGeom(objDir, "/PKMN/ZUBAT.obj", ZUBAT);
// 		initGeom(objDir, "/wt/WTStick.obj", WTStick);
// 		initGeom(objDir, "/wt/WTEng.obj", WTEng);
// 		initGeom(objDir, "/wt/WTSpin.obj", WTSpin);
// 		initGeom(objDir, "/wt/WTBlade.obj", WTBlade);
// 		initGeom(objDir, "/wt/WTFoundation.obj", WTFoundation);
// 		initGeom(objDir, "/plants/plant1.obj", P1);

// 	}

// 	void SetMaterial(int i) {
// 		prog->bind();
// 		switch (i) {
//     		case 0: //green
//     			glUniform3f(prog->getUniform("MatAmb"), 0.00, 0.70, 0.50);
//     			break;
//     		case 1: // flat grey
//     			glUniform3f(prog->getUniform("MatAmb"), 0.13, 0.13, 0.13);
//     			break;
//     		case 2: //yellow
//     			glUniform3f(prog->getUniform("MatAmb"), 0.90, 0.90, 0.00);
//     			break;
// 			case 3: //red
// 				glUniform3f(prog->getUniform("MatAmb"), 0.90, 0.00, 0.00);
// 				break;
// 			case 4: //dark green
// 				glUniform3f(prog->getUniform("MatAmb"), 0.10, 0.30, 0.10);
// 				break;
// 			case 5: //light gray 1
// 				glUniform3f(prog->getUniform("MatAmb"), 0.3, 0.3, 0.3);
// 				break;
// 			case 6: //light gray 2
// 				glUniform3f(prog->getUniform("MatAmb"), 0.45, 0.45, 0.45);
// 				break;
// 			case 7: // dark green
// 				glUniform3f(prog->getUniform("MatAmb"), 0.00, 0.35, 0.20);
// 				break;
// 			case 8: // blue
// 				glUniform3f(prog->getUniform("MatAmb"), 0.09, 0.38, 0.56);
// 				break;
// 			case 9: // gray-yellow
//     			glUniform3f(prog->getUniform("MatAmb"), 0.40, 0.45, 0.30);
//   		}
// 	}



// 	void loadWT(shared_ptr<MatrixStack> mod, float a1, float a2, float a3, float a4, float a5) {
// 		mod->pushMatrix();
// 			mod->rotate(1, vec3(1, 0, 1));

// 			// turbine stick
// 			mod->pushMatrix();
// 				shape = WTStick;
// 				mod->translate(vec3(0, a5, 0));
// 				mod->scale(vec3(0.15, 0.15, 0.15));
// 				mod->rotate(a1, vec3(a2, a3, a4));
// 				SetMaterial(5);
// 				glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 				shape->draw(prog);

// 				// top block piece
// 				mod->pushMatrix();
// 					shape = WTEng;
// 					mod->translate(vec3(-0.05, 1.1, 0));
// 					mod->scale(vec3(0.25, 0.25, 0.25));
// 					mod->rotate(-1.5 + cos(animRot/2)/5, vec3(0, 1, 0));
// 					SetMaterial(5);
// 					glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 					shape->draw(prog);

// 					// blade turning piece
// 					mod->pushMatrix();
// 						shape = WTSpin;
// 						mod->translate(vec3(1.3, 0, 0));
// 						mod->rotate(-animRot, vec3(1, 0, 0));
// 						mod->scale(vec3(0.3, 0.3, 0.3));
// 						SetMaterial(6);
// 						glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 						shape->draw(prog);

// 						mod->pushMatrix();
// 							shape = WTBlade;
// 							mod->translate(vec3(-0.4, 2.75, -1.3));
// 							mod->scale(vec3(13, 13, 13));
// 							SetMaterial(1);
// 							glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 							shape->draw(prog);
// 						mod->popMatrix();
// 					mod->popMatrix();
// 				mod->popMatrix();

// 				// base plate
// 				mod->pushMatrix();
// 					shape = WTFoundation;
// 					mod->translate(vec3(0, -1.05, 0));
// 					mod->scale(vec3(0.25, 0.25, 0.25));
// 					SetMaterial(1);
// 					glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 					shape->draw(prog);
// 				mod->popMatrix();
// 			mod->popMatrix();
// 		mod->popMatrix();
// 	}

// 	void loadPKMNC(shared_ptr<MatrixStack> mod) {
// 		mod->pushMatrix();
// 			mod->rotate(0.75, vec3(2.05, 3.4, 3.45));
// 			shape = PKMNC;
// 			mod->translate(vec3(0, 1.175, 0));
// 			mod->scale(vec3(0.35, 0.35, 0.35));
// 			mod->rotate(1.7, vec3(0, 1, 0));
// 			SetMaterial(3);
// 			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 			shape->draw(prog);

// 			mod->pushMatrix();
// 				shape = platform;
// 				mod->translate(vec3(0, -0.725, 0));
// 				mod->scale(vec3(0.82, 8.6, 2.3));
// 				SetMaterial(1);
// 				glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 				shape->draw(prog);
// 			mod->popMatrix();
// 		mod->popMatrix();
// 	}

// 	void loadPKMN(shared_ptr<MatrixStack> mod) {

// 		// loads pikachu
// 		mod->pushMatrix();
// 			mod->rotate(0.95, vec3(9.15, 3.85, 3.4));
// 			shape = PKCH;
// 			mod->rotate(3+animRot/5, vec3(0, 11, 1));
// 			mod->translate(vec3(-0.05, 1.15+((sin(animRot)+1)/(15)), 0));
// 			mod->scale(vec3(0.15, 0.15, 0.15));
// 			mod->rotate(6, vec3(0, 1, 0));
// 			SetMaterial(2);
// 			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 			shape->draw(prog);
// 		mod->popMatrix();

// 		// loads Mimikyu
// 		mod->pushMatrix();
// 			mod->rotate(0.95, vec3(9.15, 3.85, 3.4));
// 			shape = MMK;
// 			mod->rotate(animRot/5, vec3(0, 11, 1));
// 			mod->translate(vec3(-0.05, 1.15+((cos(animRot)+1)/(15)), 0));
// 			mod->scale(vec3(0.15, 0.15, 0.15));
// 			mod->rotate(4.3, vec3(0, 1, 0));
// 			SetMaterial(9);
// 			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 			shape->draw(prog);
// 		mod->popMatrix();

// 		// loads zubats
// 		glUniform1f(prog->getUniform("bendAmount"), ((0.9*cos(animRot/(-0.7)))/(1.3)));
// 		for(int i = 0; i < 9; i+=4) {
// 			mod->pushMatrix();
// 				mod->rotate(1, vec3(0.1, 0.1, -0.1));
// 				shape = ZUBAT;
// 				mod->rotate(i+animRot/5, vec3(0.2, -0.5, 0.2));
// 				mod->translate(vec3(0, 1.5, 0));
// 				mod->scale(vec3(0.1, 0.1, 0.1));
// 				mod->rotate(1, vec3(1, 0, 0));
// 				mod->rotate(0.4, vec3(0, 1, 0));
// 				mod->rotate(0.5, vec3(0, 0, 1));
// 				SetMaterial(8);
// 				glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 				shape->draw(prog);
// 			mod->popMatrix();
// 		}
// 		glUniform1f(prog->getUniform("bendAmount"), 0);
// 	}

// 	void loadPlant(shared_ptr<MatrixStack> mod, float a1, float a2, float a3, float a4) {
// 		mod->pushMatrix();
// 			mod->rotate(a1, vec3(a2, a3, a4));
// 			mod->pushMatrix();
// 				shape = P1;
// 				mod->translate(vec3(0, 1.03, 0));
// 				mod->scale(vec3(0.05, 0.05, 0.05));
// 				SetMaterial(7);
// 				glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(mod->topMatrix()));
// 				shape->draw(prog);
// 			mod->popMatrix();
// 		mod->popMatrix();
// 	}

// 	void render()
// 	{
// 		// Get current frame buffer size.
// 		int width, height;
// 		glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
// 		glViewport(0, 0, width, height);

// 		// Clear framebuffer.
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 		//Use the matrix stack for Lab 6
// 		float aspect = width/(float)height;

// 		// Create the matrix stacks - please leave these alone for now
// 		auto Projection = make_shared<MatrixStack>();
// 		auto View = make_shared<MatrixStack>();
// 		auto Model = make_shared<MatrixStack>();

// 		// Apply perspective projection.
// 		Projection->pushMatrix();
// 		Projection->perspective(45.0f, aspect, 0.01f, 100.0f);

// 		// View is identity - for now
// 		View->pushMatrix();
// 		// View->print();

// 		// Draw a stack of cubes with indiviudal transforms
// 		prog->bind();
// 		glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(Projection->topMatrix()));
// 		glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, value_ptr(View->topMatrix()));

// 		glUniform3f(prog->getUniform("LightDir"), 2, 1.5, 0);	// used for shading in one mode
// 		glUniform1i(prog->getUniform("colorMode"), colorMode);	// used to switch colors around 
		
// 		glUniform3f(prog->getUniform("lightP"), lightTrans+2, 3, 4);

// 		if (animate) animRot += 0.025;

// 		Model->pushMatrix();
// 			//global rotate (the whole scene)
// 			Model->rotate(gRot, vec3(0, 1, 0));

// 			// sphere center to place all other objects around
// 			shape = SmoothSphere;
// 			Model->translate(vec3(0, -5, -11 + gTrans));
// 			Model->scale(vec3(5.7, 5.7, 5.7));
// 			Model->rotate(-0.1 + sin(animRot/3)/10, vec3(0, 0, 1));
// 			SetMaterial(0);
// 			glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(Model->topMatrix()));
// 			shape->draw(prog);

// 			// loads wind turbine
// 			loadWT(Model, 1, 0, 0.8, 0.05, 1.175);

// 			// loads PMKN center
// 			loadPKMNC(Model);

// 			// loads PKMN
// 			loadPKMN(Model);

// 			// loads plants
// 			Model->pushMatrix();
// 				for(int j = 0; j < 17; ++j) {
// 					for(int i = 1; i < 17; ++i) {
// 						Model->rotate(j, vec3(0, 1, 0));
// 						loadPlant(Model, (0.2)*i, (-0.95)*j, (2.45)*j, (5.3)*j);
// 					}

// 				}
// 			Model->popMatrix();


// 		Model->popMatrix();

// 		prog->unbind();

// 		// Pop matrix stacks.
// 		Projection->popMatrix();
// 		View->popMatrix();

// 	}
// };

// int main(int argc, char *argv[])
// {
// 	// Where the resources are loaded from
// 	std::string resourceDir = "../resources";

// 	if (argc >= 2)
// 	{
// 		resourceDir = argv[1];
// 	}

// 	Application *application = new Application();

// 	// Your main will always include a similar set up to establish your window
// 	// and GL context, etc.

// 	WindowManager *windowManager = new WindowManager();
// 	windowManager->init(1280, 800);
// 	windowManager->setEventCallbacks(application);
// 	application->windowManager = windowManager;

// 	// This is the code that will likely change program to program as you
// 	// may need to initialize or set up different data and state

// 	application->init(resourceDir);
// 	application->initObjects(resourceDir);

// 	// Loop until the user closes the window.
// 	while (! glfwWindowShouldClose(windowManager->getHandle()))
// 	{
// 		// Render scene.
// 		application->render();

// 		// Swap front and back buffers.
// 		glfwSwapBuffers(windowManager->getHandle());
// 		// Poll for and process events.
// 		glfwPollEvents();
// 	}

// 	// Quit program.
// 	windowManager->shutdown();
// 	return 0;
// }


