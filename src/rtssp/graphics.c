/**
 * @file graphics.c
 * @author Joseph St. Pierre
 * @brief 
 * @version 0.1
 * @date 2019-11-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */


// INCLUDES //

#include "rtssp/graphics.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <math.h>
#include <assert.h>


// DEFINITIONS //

#define LOG_SIZE 512    // Allocate 512 bytes to error logs from OpenGL


// LOCAL FUNCTIONS //

// SHADER FUNCTIONS //

/**
 * @brief Local helper function for compiling a shader program
 * 
 * @param shader_path   Path to the shader program on disk
 * @param type          The type of program to compile
 * @return GLuint       Id of the shader
 */
static GLuint compileShader(const char *shader_path, GLenum type) {
  // Assertions
  assert(shader_path);  // Shader path must not be null

  // Fields
  GLuint shader;    // The shader to be compiled
  GLint success;    // Success flag
  GLchar error_log[LOG_SIZE];  // Allocate log size bytes for error logs
  FILE *file = NULL;  // The file pointer for loading the shader code from disk
  char *buffer = NULL;  // The buffer to be filled with the text of the source files
  long length;  // The length of the buffer

  /**
   * @brief Here we load and compile the shader
   * 
   */

  // FILE IO //
  file = fopen(shader_path, "r");  // The path to the shader
  assert(file); // Ensure file loaded properly

  // Find out how big the file is
  fseek(file, 0, SEEK_END);
  length = ftell(file); // Get the length of the file 
  fseek(file, 0, SEEK_SET);
  buffer = (char *)malloc(sizeof(char) * (length + 1));   // Allocate bytes for the buffer plus null terminator '\0'

  // Read data into buffer
  fread(buffer, 1, length, file);

  // Close the file
  fclose(file);

  buffer[length] = '\0';  // Add the null terminator

  // SHADER //

  // Build requested shader program
  shader = glCreateShader(type);
  glShaderSource(shader, 1, &buffer, NULL);
  glCompileShader(shader);

  free(buffer); // Free the buffer since we no longer need it

  // Check for errors
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, LOG_SIZE, NULL, error_log);

    fprintf(stderr, "Shader program failed to compile. Error: %s\n", error_log);
    exit(EXIT_FAILURE);   // Terminate program
  }

  return shader;    // Return the shader
}


// GLOBAL FUNCTIONS //

// SHADER FUNCTIONS //

GLuint compileAndLinkShaderProgram(const char *vertex_shader_path, const char *fragment_shader_path) {
  // Assertions
  assert(vertex_shader_path && fragment_shader_path);   // All programs need vertex and fragment shaders

  // OpenGL fields 
  GLuint program;  // The shader program to return
  GLuint vertex, fragment;  // The vertex and fragment shaders
  GLint success;  // Success flag
  GLchar error_log[LOG_SIZE];  // Allocate LOG_SIZE bytes for error logging

  // Load and compile the vertex and fragment shaders from disk
  vertex = compileShader(vertex_shader_path, GL_VERTEX_SHADER);   // Compile the vertex shader
  fragment = compileShader(fragment_shader_path, GL_FRAGMENT_SHADER);   // Compile the fragment shader

  // Create a program and link the shaders
  program = glCreateProgram();
  glAttachShader(program, vertex);    // Attach the vertex shader
  glAttachShader(program, fragment);  // Attach the fragment shader

  glLinkProgram(program); // Link the vertex and fragment shaders

  // Check for linker error
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(program, LOG_SIZE, NULL, error_log);   // Get the error

    fprintf(stderr, "Failed to link shaders! Error: %s\n", error_log);
    exit(EXIT_FAILURE);   // Terminate program
  }

  // Detach the shaders so they can be deleted
  glDetachShader(program, vertex);
  glDetachShader(program, fragment);

  // Delete the shaders since we have our program now
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return program;  // Return the compiled and linked program
}

void setUniformVec4(GLuint program, const char *uniform_name, vec4 vector) {
  glUniform4fv(glGetUniformLocation(program, uniform_name), 1, vector);
}

void setUniformMat4(GLuint program, const char *uniform_name, mat4 matrix) {
  glUniformMatrix4fv(glGetUniformLocation(program, uniform_name), 1, GL_FALSE, (GLfloat *)matrix);
}

void setUniformInt(GLuint program, const char *uniform_name, int v) {
  glUniform1i(glGetUniformLocation(program, uniform_name), v);
}

// TEXTURE FUNCTIONS //

texture_t createTexture2DFromImage(
  const char *filepath, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter) {
  // Fields
  texture_t texture;  // The texture to be built

  // Enable vertical flipping
  stbi_set_flip_vertically_on_load(1);
  
  // Load the image from disk and get bytes
  unsigned char *data = stbi_load(filepath, &texture.width, &texture.height, &texture.channels, 0);
  assert(data);   // Break the program if an image fails to load (bad practice I know)

  // Build a new texture and set it up with OpenGL
  glGenTextures(1, &texture.id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture.id);   

  // Set the horizontal and vertical wrapping mode
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);

  // Set minification and magnification filter parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

  // Get the mode 
  GLint mode = GL_RGB;
  if (texture.channels == 4)
    mode = GL_RGBA;

  // Send the data to OpenGL
  glTexImage2D(GL_TEXTURE_2D, 0, mode, texture.width, texture.height, 0, mode, GL_UNSIGNED_BYTE, data);

  // Generate mip maps
  glGenerateMipmap(GL_TEXTURE_2D);

  // Unbind the texture from tex unit 0 (technically not required but makes me rest easy)
  glBindTexture(GL_TEXTURE_2D, GL_NONE);

  stbi_image_free(data);  // Free the image data to prevent a memory leak

  return texture;   // Return the loaded texture
}

void freeTexture(texture_t *texture) {
  // Reset the texture to its null state
  if (texture) {
    glDeleteTextures(1, &(texture->id));
    texture->width = 0;
    texture->height = 0;
    texture->channels = 0;
  }
}

// MESH FUNCTIONS //

mesh_t buildSphereMesh(GLfloat radius, GLuint stacks, GLuint sectors) {
  // Assert the inputs are in range
  assert(sectors >= 2);
  assert(stacks >= 3);
  assert(radius > 0.0f);

  // Fields
  mesh_t sphere;  // The mesh we are going to return
  vertex_t *vertex_array = NULL;  // The vertex array to build
  GLuint *element_array = NULL;   // The element array to build

  // Compute the number of vertices to appear in the sphere
  sphere.vertex_count = (stacks + 1) * (sectors + 1);
  
  // Allocate memory for the vertex array
  vertex_array = (vertex_t *)malloc(sizeof(vertex_t) * sphere.vertex_count);

  // Compute the number of elements to appear in the sphere
  sphere.element_count = stacks * ((sectors - 2) * 6 + 2 * 3);

  // Allocate memory for the element array
  element_array = (GLuint *)malloc(sizeof(GLuint) * sphere.element_count);

  // Create a new VBO and EBO for the mesh
  glGenBuffers(1, &(sphere.vbo));
  glGenBuffers(1, &(sphere.ebo));

  // Set the draw mode of the mesh
  sphere.draw_mode = GL_TRIANGLES;

  /**
   * @brief This code for sphere construction is courtesy of Song Ho Ahn and at the time
   * of writing this program can be found and explained here: http://www.songho.ca/opengl/gl_sphere.html
   * Aside from some minor changes, the code here is identical to it.
   */

  // Temp variables for constructing the sphere
  float x, y, z, xy;  // Vertex position
  float nx, ny, nz, length_inv = 1.0f / radius;  // Vertex normal
  float u, v; // Vertex tex coords
  float sector_step = 2 * GLM_PIf / sectors; 
  float stack_step = GLM_PIf / stacks;
  float sector_angle, stack_angle;

  // Create pointers to the vertex and element arrays so we can fill them with data
  vertex_t *vertex = vertex_array;
  GLuint *element = element_array;

  /**
   * @brief Build the vertices of the sphere here
   * 
   */
  for (unsigned int i = 0; i <= stacks; i++) {
    stack_angle = GLM_PIf / 2 - i * stack_step;
    xy = radius * cosf(stack_angle);
    z = radius * sinf(stack_angle);

    // Add (sectors + 1) vertices per stack
    for (unsigned int j = 0; j <= sectors; j++) {
      sector_angle = j * sector_step;

      // Compute and set the position of the vertex
      x = xy * cosf(sector_angle);
      y = xy * sinf(sector_angle);
      vertex->position[0] = x;
      vertex->position[1] = y;
      vertex->position[2] = z;

      // Compute and set the normal vector of the vertex
      nx = x * length_inv;
      ny = y * length_inv;
      nz = z * length_inv;
      vertex->normal[0] = nx;
      vertex->normal[1] = ny;
      vertex->normal[2] = nz;

      // Compute and set the texture coords of the vertex
      u = (float)j / sectors;
      v = (float)i / stacks;
      vertex->uv[0] = u;
      vertex->uv[1] = v;

      vertex++; // Move onto next vertex
    }
  }

  /**
   * @brief Build the elements of the sphere here
   * 
   */
  for (unsigned int i = 0; i < stacks; i++) {
    unsigned int k1 = i * (sectors + 1);
    unsigned int k2 = k1 + sectors + 1;

    for (unsigned int j = 0; j < sectors; j++, k1++, k2++) {
      // 2 triangles per sector excluding first and last stacks
      // k1 => k2 => k1 + 1
      if (i != 0) {
        *element++ = k1;
        *element++ = k2;
        *element++ = k1 + 1;
      }

      // k1 + 1 => k2 => k2 + 1
      if (i != (stacks - 1)) {
        *element++ = k1 + 1;
        *element++ = k2;
        *element++ = k2 + 1;
      }
    }
  }

  // Send the vertex and element data to the vbo and ebo

  // Bind the vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, sphere.vbo);
  glBufferData(GL_ARRAY_BUFFER, sphere.vertex_count * sizeof(vertex_t), vertex_array, GL_STATIC_DRAW);

  // Bind the element buffer object
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere.element_count * sizeof(GLuint), element_array, GL_STATIC_DRAW);

  // Free the bytes of vertex_array and element_array since we no longer need them
  free(vertex_array);
  free(element_array);

  return sphere;  // Return the sphere created
}

mesh_t buildIcosphereMesh(GLfloat radius, GLuint subdivisions) {
  // Fields
  mesh_t icosphere;
  
  /**
   * @brief This code for sphere construction is courtesy of Song Ho Ahn and at the time
   * of writing this program can be found and explained here: http://www.songho.ca/opengl/gl_sphere.html
   * Aside from some minor changes, the code here is identical to it.
   */

  // Variables for Icosphere creation
  const float H_ANGLE = GLM_PIf / 180.0f * 72.0f;   // 72 degrees
  const float V_ANGLE = atanf(1.0f / 2.0f);         // Elevation = 26.565 degrees

  /*
    TODO: Figure out how to create an Icosphere in C.
  */ 


  return icosphere; // Return the icosphere created
}

void freeMesh(mesh_t *mesh) {
  // If pointer is valid
  if (mesh) {
    glDeleteBuffers(1, &(mesh->vbo));   // Delete the vbo
    glDeleteBuffers(1, &(mesh->ebo));   // Delete the ebo

    // Set everything to 0
    mesh->vbo = GL_NONE;
    mesh->ebo = GL_NONE;
    mesh->draw_mode = GL_NONE;
    mesh->element_count = 0;
    mesh->vertex_count = 0;
  }
}

// INTERPOLATION FUNCTIONS //

void interpolate(interpol_t state, float alpha, vec3 dest) {
  // Interpolate between curr and prev
  dest[0] = (state.curr[0] * alpha) + (state.prev[0] * (1.0f - alpha));
  dest[1] = (state.curr[1] * alpha) + (state.prev[1] * (1.0f - alpha));
  dest[2] = (state.curr[2] * alpha) + (state.prev[2] * (1.0f - alpha));
}

// RENDERABLE FUNCTIONS //

renderable_t buildRenderable(mesh_t mesh, texture_t texture, vec3 position, vec3 rotation, vec3 scale) {
  renderable_t renderable;  // The renderable to build

  // Copy trivial data
  renderable.mesh = mesh;
  renderable.texture = texture;

  // Copy vectors for the model matrix
  glm_vec3_copy(position, renderable.model_fields.position.curr);
  glm_vec3_copy(position, renderable.model_fields.position.prev);
  glm_vec3_copy(rotation, renderable.model_fields.rotation.curr);
  glm_vec3_copy(rotation, renderable.model_fields.rotation.prev);
  glm_vec3_copy(scale, renderable.model_fields.scale.curr);
  glm_vec3_copy(scale, renderable.model_fields.scale.prev);

  // Compute model matrix from position, rotation, and scale
  buildModelMatrix(position, (vec3){0.0f, 0.0f, 0.0f}, rotation, scale, renderable.model_matrix);

  return renderable;
}

// CAMERA FUNCTIONS //

camera_t buildCamera(float fov, float aspect, float z_near, float z_far, vec3 position, vec3 at, vec3 up) {
  camera_t camera;  // The camera to build

  // Set projection matrix parameters
  camera.projection_fields.fov = fov;
  camera.projection_fields.aspect = aspect;
  camera.projection_fields.z_far = z_near;
  camera.projection_fields.z_near = z_far;

  // Copy vectors for the view matrix
  glm_vec3_copy(position, camera.view_fields.position.curr);
  glm_vec3_copy(position, camera.view_fields.position.prev);
  glm_vec3_copy(at, camera.view_fields.at);
  glm_vec3_copy(up, camera.view_fields.up);

  // Build matrices
  mat4 projection_matrix;
  mat4 view_matrix;

  glm_perspective(fov, aspect, z_near, z_far, projection_matrix);
  glm_lookat(position, at, up, view_matrix);

  // View Projection matrix multiplication
  glm_mat4_mul(projection_matrix, view_matrix, camera.view_projection_matrix);

  // Return camera
  return camera;
}

// MATRIX FUNCTIONS //

void buildModelMatrix(vec3 position, vec3 pivot, vec3 rotation, vec3 scale, mat4 model_matrix) {
  vec3 combinedTranslation;   // The sum of position + pivot
  glm_vec3_add(position, pivot, combinedTranslation);

  glm_mat4_identity(model_matrix);  // Initialize identity matrix
  glm_translate(model_matrix, combinedTranslation);   // Move to pos + pivot

  // TODO: These rotation calculations might cause a gimbal lock, consider using quaternions
  glm_rotate(model_matrix, glm_rad(rotation[1]), (vec3){0.0f, 1.0f, 0.0f}); // Rotate around y axis
  glm_rotate(model_matrix, glm_rad(rotation[0]), (vec3){1.0f, 0.0f, 0.0f}); // Rotate around x axis
  glm_rotate(model_matrix, glm_rad(rotation[2]), (vec3){0.0f, 0.0f, 1.0f}); // Rotate around z axis

  glm_scale(model_matrix, scale); // Scale the matrix

  vec3 inv;   // Vector to bring us back to position
  glm_vec3_scale(pivot, -1.0f, inv);
  glm_translate(model_matrix, inv); // Translate back to the position
}