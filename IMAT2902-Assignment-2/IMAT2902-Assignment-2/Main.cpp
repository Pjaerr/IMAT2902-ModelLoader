#include "stdafx.h"
#include "Main.h"
#include "Model.h"


Main::Main()
{
	scene = Scene(); //!< Create an empty scene passing in the shader program.
}

Main::~Main()
{
}

/*! Creates and sets up an OpenGL Context within the Window that was created within InitProgram.*/
void Main::CreateGLWindow(HWND hWnd, RECT rect)
{
	m_win32OpenGL.CreateGLContext(hWnd); //Creates an OpenGL context in the current window received from InitProgram

	scene.camera.m_aspectRatio = static_cast<float>(rect.right / rect.bottom); //Sets up the aspect ratio.

	m_win32OpenGL.CreateShadersAndProgram("phongTexture2"); //Setup the shader program with the given shader file[s].

	m_win32OpenGL.SetupDisplay();

	glEnable(GL_BLEND);


	m_win32OpenGL.GetError(); //Checks everything is ok.
}

/*! Destroys the OpenGL Context.*/
void Main::DestroyGLWindow()
{
	m_win32OpenGL.TearDownGLContext();
}

/*! Initiates the computation of both the View and Projection matrices. Sends both the
*	matrices as well as the lighting vectors to the shader and then setups the Scene object
*	which controls the models within the scene.
*/
void Main::PrepareToDraw()
{
	glClearColor(0, 92, 103, 255);
	//View and Projection Matrices are computed in Camera class when it is constructed.
	GLuint program = m_win32OpenGL.GetShaderProgram(); //Get the shader program.

	/*Send the both the projection and view matrices as well as the lighting vectors to the shader.*/

	//Matrices
	Win32OpenGL::SendUniformMatrixToShader(program, scene.camera.projectionMatrix, "projection_matrix");
	Win32OpenGL::SendUniformMatrixToShader(program, scene.camera.viewMatrix, "view_matrix");

	//Lighting Vectors
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightPosition, "light_position_world");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightColourSpecular, "light_colour_specular");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightColourDiffuse, "light_colour_diffuse");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightColourAmbient, "light_colour_ambient");

	scene.Start(); //Start the Scene.
}

/*! Clears the OpenGL display and then gets the shader program. It then calls Scene::Render()
*	which will call the draw functions of any models within the scene.*/
void Main::Draw()
{
	m_win32OpenGL.ClearGLDisplay(); //Clear the OpenGL Display.

	GLuint program = m_win32OpenGL.GetShaderProgram(); //Get the shader program.

	scene.Render(program); //Draw all models in the scene.

	m_win32OpenGL.FinishedDrawing();
}

/*! Calls the Scene::Update() method which will carry out any model transformations and
*	other actions that need to occur every tick but aren't directly related to drawing.*/
void Main::Update()
{
	scene.Update(); //Update the scene.
}

/*! Receives input from InitProgram and carries out actions related to that input.
*	For now it handles moving the camera around the scene.*/
void Main::HandleInput(unsigned char virtualKeyCode)
{
	scene.keyIsPressed(virtualKeyCode);
}

void Main::HandleMouseInput(int xPosRelative, int yPosRelative)
{
	scene.mouseIsMoved(xPosRelative, yPosRelative);
}

/*! Handles the window being resized and updating OpenGL of the action so it can
*	compute the correct projection matrix.*/
void Main::Resize(HDC hdc, RECT rect)
{
	// if the display is resized then OpenGL needs to know about the apect ratio
	// to compute the correct projection matrix
	m_win32OpenGL.Reshape(hdc, rect.right, rect.bottom);
	scene.camera.m_aspectRatio = (float)rect.right / rect.bottom;
	scene.camera.computeProjectionMatrix();
	GLuint program = m_win32OpenGL.GetShaderProgram();
	Win32OpenGL::SendUniformMatrixToShader(program, scene.camera.projectionMatrix, "projection_matrix");
}