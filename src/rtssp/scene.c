/**
 * @file scene.c
 * @author Joseph St. Pierre
 * @brief 
 * @version 0.1
 * @date 2019-11-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */


// INCLUDES //

#include "rtssp/scene.h"


// DATA //

GLuint vao;   // The vertex array object 


// FUNCTIONS //

void initScene(void) {
  glGenVertexArrays(1, &vao); // Generate a vertex array object


}

void updateScene(float dt) {
  /**
   * @brief TODO: 
   * 
   */
}

void drawScene(float alpha) {
  /**
   * @brief Here OpenGL draws everything in the scene to the default framebuffer which will be
   * sent to the screen by GLFW during the swapbuffers() call
   * 
   */

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set the clear color to black
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer and depth buffer

  glBindVertexArray(vao); // Bind the vao for drawing


}

void freeScene(void) {


  glDeleteVertexArrays(1, &vao);  // Delete the vertex array object
}