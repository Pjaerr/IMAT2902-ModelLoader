/*! \file Main.h
*	Contains the bulk of the application code. Functions from here are called via InitProgram.cpp
*	Main initialises and interfaces with OpenGL via Win32OpenGL.
*/

#pragma once

#define _USE_MATH_DEFINES //!< For M_PI Constant.
#include <cmath>

#include "Win32OpenGL.h" //!< Use OpenGL.
#include "resource.h"
#include "Log.h"
#include "Scene.h"

class Main
{
	Win32OpenGL m_win32OpenGL; //!< OpenGL helper class.

	/*! Camera positions (X, Y, Z)*/
	float m_cameraX{ 0 };
	float m_cameraY{ 0 };
	float m_cameraZ{ 2.5f };

	/*! Matrices*/
	glm::mat4 m_viewMatrix; //!< Contains data for the view.
	glm::mat4 m_projectionMatrix; //!< Contains data for the projection.

	/*! Temporary variables for testing rotation of models.*/
	float m_xAngle{ 0.0f };
	float m_yAngle{ 0.0f };
	float m_zAngle{ 0.0f };


	float m_aspectRatio; //!< The aspect ratio of the view.

	/*! Lighting vectors, to be sent to the shader.*/
	glm::vec3 m_lightColourSpecular{ 1.0f,1.0f,1.0f };
	glm::vec3 m_lightColourDiffuse{ 0.8f, 0.8f, 0.8f };
	glm::vec3 m_lightColourAmbient{ 0.3f, 0.3f, 0.3f };
	glm::vec3 m_lightPosition{ 0.0f, 5.0f, 5.0f };

	Scene scene; //!< The scene that controls all of the models.

public:
	Main();
	~Main();

	/*! Creates and sets up an OpenGL Context within the Window that was created within InitProgram.*/
	void CreateGLWindow(HWND hWnd, RECT rect);

	/*! Destroys the OpenGL Context.*/
	void DestroyGLWindow();

	/*! Initiates the computation of both the View and Projection matrices. Sends both the
	*	matrices as well as the lighting vectors to the shader and then setups the Scene object
	*	which controls the models within the scene.
	*/
	void PrepareToDraw();

	/*! Clears the OpenGL display and then gets the shader program. It then calls Scene::Render()
	*	which will call the draw functions of any models within the scene.
	*/
	void Draw();

	/*! Calls the Scene::Update() method which will carry out any model transformations and 
	*	other actions that need to occur every tick but aren't directly related to drawing.
	*/
	void Update();

	/*! Receives input from InitProgram and carries out actions related to that input.
	*	For now it handles moving the camera around the scene.
	*/
	void HandleInput(unsigned char virtualKeyCode);

	/*! Handles the window being resized and updating OpenGL of the action so it can
	*	compute the correct projection matrix.
	*/
	void Resize(HDC hdc, RECT rect);

	/*! Computes a projection matrix and stores it as a glm::mat4 inside of m_projectionMatrix*/
	void ComputeProjectionMatrix();

	/*! Computes a view matrix that allows the implementation of a camera. Stores the matrix as
	*	a glm::mat4 inside of m_viewMatrix.
	*/
	void ComputeViewMatrix();
};