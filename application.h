#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "game.h"
#include "constant.h"

#pragma once
class Application
{
public :
	Application();
	~Application();
	
private :
	bool Init();
	void Update();
	void Draw();

	void ProcessInput(GLFWwindow* window);
	
	Shader mainShader; 
	GLFWwindow* window;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};

extern Application* meApp;