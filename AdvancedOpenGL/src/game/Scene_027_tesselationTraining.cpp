

#include "Scene_027_tesselationTraining.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

#include "CubeMesh.h"


Scene_027_tesselationTraining::Scene_027_tesselationTraining()
{
}

Scene_027_tesselationTraining::~Scene_027_tesselationTraining() {
    clean();
}

void Scene_027_tesselationTraining::setGame(Game *_game) {
    game = _game;
}

void Scene_027_tesselationTraining::load() {
    std::srand((int) std::time(nullptr));

    // Loading all the shaders
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), "", SHADER_ID(SHADER_NAME));
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

    // Setup openGL to show tesselation
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // Load the mesh
    cubeMesh = new CubeMesh();
    cubeMesh->load();

    // Get the shader
    shader = Assets::getShader(SHADER_ID(SHADER_NAME));

    // Emplace the cube in the cubes array
    cubes.emplace_back(0.0f, 0.0f, cubeMesh);
}

void Scene_027_tesselationTraining::clean() {
    cubeMesh->clean();
    delete cubeMesh;
}

void Scene_027_tesselationTraining::pause() {
}

void Scene_027_tesselationTraining::resume() {
}

void Scene_027_tesselationTraining::handleEvent(const InputState &inputState) {
}

void Scene_027_tesselationTraining::update(float dt) {
    // Stock the elapsed time since the beginning of the script
    elapsedTime += dt;

    // Update the cube
    for (auto& cube : cubes) {
        cube.update();
    }

    // Rotate the cube depending on elapsed time
    cubes[0].setRotation(cubes[0].getRotation() + 1.f * dt);

    // Modifying inner and outer values separately to create a cool effect
    inner = (sin(elapsedTime * 0.2)+1)*3;
    outer = (cos(elapsedTime * 1.2)+1)*3;
}

void Scene_027_tesselationTraining::draw() {
    // Setting up the background
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
    
    // Updating the different uniforms in the shaders
    shader.use();
    shader.setMatrix4("proj_matrix", projection);
    shader.setFloat("inner", inner);
    shader.setFloat("outer", outer);

    // Prepare openGL to draw in a specific way
    glPatchParameteri(GL_PATCH_VERTICES, 3);

    // Draw
    for (auto& cube : cubes) {
        cube.draw(shader);
    }
}
