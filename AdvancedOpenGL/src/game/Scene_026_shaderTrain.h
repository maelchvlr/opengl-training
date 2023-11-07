
#ifndef Scene_026_shaderTrain_H
#define Scene_026_shaderTrain_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_026_shaderTrain : public Scene {
public:
    Scene_026_shaderTrain();
    ~Scene_026_shaderTrain();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState&);
    void update(float dt);
    void draw();
    void setGame(Game*);

private:
    Game* game;
    GLuint vao;
    GLuint buffer;
    Matrix4 transform[2];
    Matrix4 projection;
    int colorModeCube0 = 0;
    int colorModeCube1 = 1;
    float frequency = 10;

    Shader shader;
};


#endif //Scene_026_shaderTrain_H

