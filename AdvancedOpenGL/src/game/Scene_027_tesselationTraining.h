//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_027_tesselationTraining_H
#define Scene_027_tesselationTraining_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

#include "CubeObject.h"

class CubeMesh;

class Scene_027_tesselationTraining : public Scene {
public:
    Scene_027_tesselationTraining();
    ~Scene_027_tesselationTraining();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

    float inner = 3.0;
    float outer = 3.0;
    float elapsedTime = 0.f;

private:
    Game *game;
    CubeMesh* cubeMesh;

    Matrix4 projection;
    Shader shader;

    vector<CubeObject> cubes;
    float newXPosition { 0 };
};


#endif //Scene_027_tesselationTraining_H
