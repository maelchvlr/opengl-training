//
// Created by gaetz on 04/12/2019.
//

#include "Scene_026_shaderTrain.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>
#include <random>


Scene_026_shaderTrain::Scene_026_shaderTrain()
{
}

Scene_026_shaderTrain::~Scene_026_shaderTrain() {
    clean();
}

void Scene_026_shaderTrain::setGame(Game* _game) {
    game = _game;
}

void Scene_026_shaderTrain::load() {
    std::srand((int)std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    static const GLfloat vertexPositions[] =
    {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f,  0.25f,

            -0.25f,  0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
             0.25f,  0.25f,  0.25f,

             0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f, -0.25f
    };

    // Generate data and put it in buffer object
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_026_shaderTrain::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_026_shaderTrain::pause() {
}

void Scene_026_shaderTrain::resume() {
}

void Scene_026_shaderTrain::handleEvent(const InputState& inputState) {
}

void Scene_026_shaderTrain::update(float dt) {

    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0, 10);

    float timeValue = Timer::getTimeSinceStart();


    float horizontalMovement = sin(0.5f * timeValue) * 5.0f;

    // Only translate along the X-axis for horizontal movement
    transform[0] = Matrix4::createTranslation(Vector3(horizontalMovement, 0.0f, -10.0f));
    transform[1] = Matrix4::createTranslation(Vector3(-horizontalMovement, 0.0f, -10.0f));

    shader.use();

    if (abs(horizontalMovement) < 0.1f) {
        // Swap color modes when cubes are near the center
        std::swap(colorModeCube0, colorModeCube1);
        shader.setFloat("timeAtSwitch", timeValue);

        // change color switch speed
        frequency = distribution(generator);

        shader.setInteger("frequency", frequency);


    }

    shader.setFloat("time", timeValue);


}

void Scene_026_shaderTrain::draw()
{
    static const GLfloat bgColor[] = { 210.0f, 210.0f, 207.0f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    shader.setMatrix4("proj_matrix", projection);

    // Drawing Cube 0 with its specific settings
    shader.setInteger("colorMode", colorModeCube0);
    shader.setMatrix4("mv_matrix", transform[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Drawing Cube 1 with its specific settings
    shader.setInteger("colorMode", colorModeCube1);
    shader.setMatrix4("mv_matrix", transform[1]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
