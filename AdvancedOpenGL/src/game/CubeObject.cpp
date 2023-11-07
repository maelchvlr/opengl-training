#include "CubeObject.h"
#include "../engine/Shader.h"
#include "CubeMesh.h"

CubeObject::CubeObject(float xP, float yP, CubeMesh* cubeMeshP)
: cubeMesh { cubeMeshP }
{
  setPosition(xP, yP);
}

void CubeObject::update() {

}

void CubeObject::draw(Shader& shader) {

    shader.setMatrix4("mv_matrix", transform);
    cubeMesh->drawPatches(); 
}

void CubeObject::setPosition(float xP, float yP) {
  x = xP;
  y = yP;
  transform = computeTransform();
}

void CubeObject::setRotation(float angle)
{
	rotationAngle = angle;
	transform = computeTransform();
}

Matrix4 CubeObject::computeTransform() {
    Matrix4 translation = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -4.0f));
    Matrix4 rotation = Matrix4::createRotationY(rotationAngle);
    return translation * rotation;
}