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
#include "rtssp/rtssp.h"


// LOCAL DATA //

static GLuint vao;        // The vertex array object
static GLuint program;    // The shader program


// GLOBAL DATA //

camera_t camera;    // The camera for our scene


// FUNCTIONS //

void initScene(void) {
  glGenVertexArrays(1, &vao); // Generate a vertex array object

  // Build meshes and format them with the vao

  // Compile and link shader program
  program = compileAndLinkShaderProgram(SCENE_VERTEX_SHADER_DIR, SCENE_FRAGMENT_SHADER_DIR);

  // Setup the camera
  camera = buildCamera(
    DEFAULT_CAMERA_FOV, 
    (float)DEFAULT_WINDOW_WIDTH_PIXELS / (float)DEFAULT_WINDOW_HEIGHT_PIXELS,
    DEFAULT_CAMERA_Z_NEAR,
    DEFAULT_CAMERA_Z_FAR,
    (vec3){0.0f, 0.0f, 0.0f},   // Start at center of the world coordinates
    (vec3){0.0f, 0.0f, 1.0f},   // Look straight ahead
    (vec3){0.0f, 1.0f, 0.0f}    // Up vector (shouldn't ever change)
  );
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
  // Delete all the meshes and renderables

  glDeleteVertexArrays(1, &vao);  // Delete the vertex array object
}