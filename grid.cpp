#include "grid.h"

Grid::Grid(Camera* camera, std::vector<glm::vec3, std::allocator<glm::vec3>>* cubesPositions)
{
	mCamera = camera;
	mCubesPositions = cubesPositions;
}

Grid::~Grid()
{
}

void Grid::GetPointedGridChunk()
{
	float t = -(mCamera->Position.y / mCamera->Front.y);

	float x = mCamera->Position.x + mCamera->Front.x * t;
	float z = mCamera->Position.z + mCamera->Front.z * t;

	mGridChunk = glm::vec2((int)(x / mChunkSize), (int)(z / mChunkSize));
}

void Grid::UpdatePreview()
{
	(*mCubesPositions)[mCubesPositions->size() - 1] = glm::vec3(mGridChunk.x + mChunkSize / 2, 0, mGridChunk.y + mChunkSize / 2);

	mCanBuild = true;
	for (int i = 0; i < mCubesPositions->size() - 1; i++)
	{
		if (glm::abs((*mCubesPositions)[i].x - (*mCubesPositions)[mCubesPositions->size() - 1].x) < 1 && glm::abs((*mCubesPositions)[i].y - (*mCubesPositions)[mCubesPositions->size() - 1].y) < 1 && glm::abs((*mCubesPositions)[i].z - (*mCubesPositions)[mCubesPositions->size() - 1].z) < 1)
		{
			mCanBuild = false;
		}
	}

}

void Grid::Build()
{
	if (mIsOpen && mCanBuild)
	{
		std::cout << "build" << std::endl;
		mCubesPositions->push_back(glm::vec3(mGridChunk.x + mChunkSize / 2, 0, mGridChunk.y + mChunkSize / 2));
	}
}

void Grid::Open()
{
	if (!mIsOpen)
	{
		mIsOpen = true;
		mCubesPositions->push_back(glm::vec3(mGridChunk.x + mChunkSize / 2, 0, mGridChunk.y + mChunkSize / 2));
	}
}

void Grid::Close()
{
	if (mIsOpen)
	{
		mIsOpen = false;
		mCubesPositions->pop_back();
	}
}

bool Grid::IsOpen()
{
	return mIsOpen;
}

bool Grid::CanBuild()
{
	return mCanBuild;
}
