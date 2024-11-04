#include "camera.h"
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

class Grid
{
public :
	Grid(Camera* camera, std::vector<glm::vec3, std::allocator<glm::vec3>>* cubesPositions);
	~Grid();

	void GetPointedGridChunk();
	void UpdatePreview();
	void Build();
	void Open();
	void Close();

	bool IsOpen();
	bool CanBuild();

private :
	Camera* mCamera;
	std::vector<glm::vec3>* mCubesPositions;
	glm::vec2 mGridChunk;
	int mChunkSize = 1;
	int mGridHeight = 0;
	bool mIsOpen = false;
	bool mCanBuild = true;
};