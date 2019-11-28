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
phys_object_t sol;  // The sun at the center of the solar system

// FUNCTIONS //

// PHYSICS OBJECT FUNCTIONS //

phys_object_t buildPhysicsObject(
  mesh_t mesh, texture_t texture, highp_vec3 position, highp_vec3 rotation, highp_vec3 scale, double mass) {
  /**
   * @brief Here we construct a physics object like a planet or moon
   * 
   */

  phys_object_t object;   // The object to build

  // Construct the renderable for the phys object making sure to convert to rendering coordinatesh
  vec3 glm_pos; convertHighPVector(&position, glm_pos, DEFAULT_HIGHP_TO_VEC3_SCALE_FACTOR);
  vec3 glm_rot; convertHighPVector(&rotation, glm_rot, DEFAULT_HIGHP_TO_VEC3_SCALE_FACTOR);
  vec3 glm_scl; convertHighPVector(&scale, glm_scl, DEFAULT_HIGHP_TO_VEC3_SCALE_FACTOR);
  object.renderable = buildRenderable(mesh, texture, glm_pos, glm_rot, glm_scl);

  // Copy position, rotation, and mass
  object.position = position;
  object.rotation = rotation;
  object.mass = mass;

  return object;    // Return the object
}

// SCENE FUNCTIONS //

void initScene(void) {
  glGenVertexArrays(1, &vao); // Generate a vertex array object

  // Build meshes and format them with the vao
  glBindVertexArray(vao);   // Bind the vao state

  


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

void drawRenderable(renderable_t renderable, float alpha) {
  /**
   * @brief This method of drawing is pretty inefficient and will cause problems as the number
   * of drawcalls gets large. To rectify the issue, later on we should refactor the code to allow
   * for instancing
   */

  // Bind the vbo and ebo of the renderable
  glBindBuffer(GL_ARRAY_BUFFER, renderable.mesh.vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderable.mesh.ebo);

  // Compute interpolated vectors
  vec3 position_int; interpolate(renderable.model_fields.position, alpha, position_int);
  vec3 rotation_int; interpolate(renderable.model_fields.rotation, alpha, rotation_int);
  vec3 scale_int; interpolate(renderable.model_fields.scale, alpha, scale_int);

  // Build the model matrix using interpolated states
  buildModelMatrix(position_int, (vec3){0.0f, 0.0f, 0.0f}, rotation_int, scale_int, renderable.model_matrix);

  // Build the MVP matrix using the model matrix and camera view and projection matrices
  mat4 MVP; glm_mat4_mul(camera.view_projection_matrix, renderable.model_matrix, MVP);

  // Send the MVP matrix to the shader
  setUniformMat4(program, "MVP", MVP);

  // Check if we need to bind a texture
  if (renderable.texture.id) {
    // Set the active texture
    glActiveTexture(GL_TEXTURE0);   // Attach to texture unit 0

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, renderable.texture.id);  // Bind the texture
    setUniformInt(program, "diffuse_map", renderable.texture.id);

    // Set texture flag to true
    setUniformInt(program, "use_texture", true);
  }
  else {
    // Set texture flag to false
    setUniformInt(program, "use_texture", false);
  }

  // Draw the buffers using the appropriate draw mode and number of elements to draw
  glDrawElements(renderable.mesh.draw_mode, renderable.mesh.element_count, GL_UNSIGNED_INT, (const GLvoid *)0);
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
  glUseProgram(program);  // Use the shader program

  // Draw the camera


  // Draw the sun
  drawRenderable(sol.renderable, alpha); 

  // Draw the planets and moons etc.
}

void freeScene(void) {
  // Delete all the meshes and renderables

  glDeleteVertexArrays(1, &vao);  // Delete the vertex array object
  glDeleteProgram(program);   // Delete the program object
}