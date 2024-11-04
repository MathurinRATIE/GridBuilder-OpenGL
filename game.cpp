#include "game.h"

Game::Game(Shader* mainShader, Camera *camera)
{
    mMainShader = mainShader;
    mCamera = camera;

	Init();
}

Game::~Game()
{
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
}

void Game::Init()
{ //------------DATAS-------------
    // Squares Vertices
    float vertices[] = {
        // positions          // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // Cubes Positions
    mCubesPositions = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Create Vertex Array Object
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Create Vertex Buffer Object
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attibute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture attibute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Get Max vertex attributes for this hardware
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    //-----------TEXTURES-------------
    // Create Texture
    glGenTextures(1, &mTexture1);
    int width, height, nrChannels;

    // Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // x repeat mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    // y repeat mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  // take linearly two nearest minimaps and linearly choose the frag color from them
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);         // take average frag color if bigger than image
    stbi_set_flip_vertically_on_load(true);

    // Texture 1
    glBindTexture(GL_TEXTURE_2D, mTexture1);

    // Retrieve Image Datas
    unsigned char* data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);

    // Apply Datas to Texture
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    mMainShader->use();
    mMainShader->setInt("texture1", 0);

    // init grid
    mGrid = new Grid(mCamera, &mCubesPositions);
}

void Game::Update(float deltaTime)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture1);

    mMainShader->use();

    //-----------3D-MATRIX-----------        
    // View Matrix : World Space --> View Space
    glm::mat4 view = mCamera->GetViewMatrix();

    // Projection Matrix : View Space --> Clip Space
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(mCamera->Zoom), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

    // Apply 3D Matrixs / Coordinate System
    //mainShader.setMat4("model", model);
    mMainShader->setMat4("view", view);
    mMainShader->setMat4("projection", projection);
    mMainShader->setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));

    // Draw Texture
    glBindVertexArray(mVAO);
    for (unsigned int i = 0; i < mCubesPositions.size(); i++)
    {
        // Model Matrix : Local Space --> World Space
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, mCubesPositions[i]);
        //float angle = 20.0f * i;
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
        mMainShader->setMat4("model", model);

        if (mGrid->IsOpen() && i == mCubesPositions.size() - 1)
        {
            mGrid->GetPointedGridChunk();
            mGrid->UpdatePreview();

            if (mGrid->CanBuild())
            {
                mMainShader->setVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));
            }
            else
            {
                mMainShader->setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Game::Draw()
{
}