#include "CubeMesh.h"
#include "../engine/Log.h"

void CubeMesh::load() {
    // Generate a Vertex Array Object (VAO) to hold the state of our vertex attributes and the Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Bind the VAO. Binding a VAO means that we're using it and any vertex attribute and buffer object changes will be recorded by it.
    glBindVertexArray(vao);

    // Define a static array of vertex positions for the cube
    // Each group of three values represents a vertex's x, y, z coordinates
    // Since a cube has 6 faces and each face has 2 triangles, we need 6 * 2 = 12 triangles with 3 vertices each, so 36 vertices in total.
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
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);


  // Vertex position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Unbind vao
  glBindVertexArray(0);


}

void CubeMesh::draw() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void CubeMesh::drawPatches() {
    glBindVertexArray(vao);
    glDrawArrays(GL_PATCHES, 0, 36);
    glBindVertexArray(0);
}

void CubeMesh::clean() {
  glDeleteVertexArrays(1, &vao);
}