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

	m_aspectRatio = static_cast<float>(rect.right / rect.bottom); //Sets up the aspect ratio.

	m_win32OpenGL.CreateShadersAndProgram("phong"); //Setup the shader program with the given shader file[s].

	m_win32OpenGL.SetupDisplay();

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
	/*Compute the projection and view matrices.*/
	ComputeProjectionMatrix();
	ComputeViewMatrix();

	
	GLuint program = m_win32OpenGL.GetShaderProgram(); //Get the shader program.

	/*Send the both the projection and view matrices as well as the lighting vectors to the shader.*/

	//Matrices
	Win32OpenGL::SendUniformMatrixToShader(program, m_projectionMatrix, "projection_matrix");
	Win32OpenGL::SendUniformMatrixToShader(program, m_viewMatrix, "view_matrix");

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

/*! Handles the window being resized and updating OpenGL of the action so it can
*	compute the correct projection matrix.*/
void Main::Resize(HDC hdc, RECT rect)
{
	// if the display is resized then OpenGL needs to know about the apect ratio
	// to compute the correct projection matrix
	m_win32OpenGL.Reshape(hdc, rect.right, rect.bottom);
	m_aspectRatio = (float)rect.right / rect.bottom;
	ComputeProjectionMatrix();
	GLuint program = m_win32OpenGL.GetShaderProgram();
	Win32OpenGL::SendUniformMatrixToShader(program, m_projectionMatrix, "projection_matrix");
}

/*! Computes a projection matrix and stores it as a glm::mat4 inside of m_projectionMatrix*/
void Main::ComputeProjectionMatrix()
{
	// we will look at this later in the course
	// in Modern OpenGL we must supply a projection matrix
	const float oneDegreeInRadians = static_cast<float>((2.0 * M_PI) / 360.0);
	//ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444

	// input variables
	float zNear = 0.1f;		// clipping plane
	float zFar = 100.0f;	// clipping plane
	float fov = static_cast<float>(67.0f * oneDegreeInRadians); // convert 67 degrees to radians

	float range = tan(fov * 0.5f) * zNear;
	float Sx = (2.0f * zNear) / (range * m_aspectRatio + range * m_aspectRatio);
	float Sy = zNear / range;
	float Sz = -(zFar + zNear) / (zFar - zNear);
	float Pz = -(2.0f * zFar * zNear) / (zFar - zNear);
	GLfloat proj_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f,
		0.0f, 0.0f, Pz, 0.0f
	};
	m_projectionMatrix = glm::make_mat4(proj_mat);
}

/*! Computes a view matrix that allows the implementation of a camera. Stores the matrix as
*	a glm::mat4 inside of m_viewMatrix.*/
void Main::ComputeViewMatrix()
{
	// the view matrix allows us to implement a camera.
	// this is based on Anton's simpler version (see recommended books)  
	// - later we implement a lookAt matrix here....
	float cam_pos[] = { m_cameraX, m_cameraY, m_cameraZ }; // don't start at zero, or we will be too close
	float cam_cameraYaw = 0.0f; // y-rotation in degrees

	glm::mat4 T = translate(glm::mat4(1.0f), glm::vec3(-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	glm::mat4 R = glm::rotate(glm::mat4(1.0f), -cam_cameraYaw, glm::vec3(0.0f, 1.0f, 0.0f));
	m_viewMatrix = R * T;
}