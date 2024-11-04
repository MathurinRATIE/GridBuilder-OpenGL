#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "constant.h"
#include "grid.h"

class Game
{
public:
	Game(Shader* mainShader, Camera* camera);
	~Game();

	void Init();
	void Update(float deltaTime);
	void Draw();

	Grid* mGrid;

private:
	Shader* mMainShader;
	Camera* mCamera;
	std::vector<glm::vec3> mCubesPositions;
	unsigned int mVAO;
	unsigned int mVBO;
	unsigned int mTexture1;
};

extern Game* meGame;