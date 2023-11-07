//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_008_SpinningCubes_H
#define Scene_008_SpinningCubes_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_008_SpinningCubes : public Scene {
public:
    Scene_008_SpinningCubes();
    ~Scene_008_SpinningCubes();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;
    GLuint vao;
    GLuint buffer;
    Matrix4 transform[2];
    Matrix4 projection;
    int colorModeCube0 = 0; 
    int colorModeCube1 = 1; 
    float frequency = 10;

    Shader shader;
};


#endif //Scene_008_SpinningCubes_H
