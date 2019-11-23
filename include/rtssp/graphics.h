/**
 * @file graphics.h
 * @author Joseph St. Pierre
 * @brief This file contains the 
 * @version 0.1
 * @date 2019-11-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _RTSSP_GRAPHICS_H_
#define _RTSSP_GRAPHICS_H_


// INCLUDES //

#include <glad/glad.h>
#include <cglm/cglm.h>


// STRUCTS //

/**
 * @brief A vertex_t contains all the data pertaining to a vertex in 3D space
 * 
 */
typedef struct {
  vec3 position;    // The position of the vertex in cartesian space
  vec3 normal;      // The normal vector for the vertex
  vec2 uv;          // The uv coordinates for texture mapping
} vertex_t;

/**
 * @brief A texture_t contains all the relevant data to a texture in VRAM
 * 
 */
typedef struct {
  GLuint id;        // The texture id
  GLsizei width;    // The width of the texture   (in pixels)
  GLsizei height;   // The height of the texture  (in pixels)
  GLsizei channels; // The number of bytes per pixel (1-4)
} texture_t;

/**
 * @brief A mesh_t contains all the data required to describe an arbitrary
 * piece of geometry
 * 
 */
typedef struct {
  GLuint  vbo;            // The vertex buffer storing the raw vertex data
  GLuint  ebo;            // The element buffer storing the primitives
  GLenum  draw_mode;      // The draw mode to use (usually will be GL_TRIANGLES)
  GLsizei vertex_count;   // The number of vertices to be rendered
  GLsizei element_count;  // The number of elements to be rendered
} mesh_t;

/**
 * @brief A renderable_t points contains everything required to draw
 * a piece of geometry at a certain position and texture
 */
typedef struct {
  mesh_t mesh;          // The mesh for the renderable
  mat4 model_matrix;    // The model matrix for the renderable
  texture_t texture;    // The texture of the renderable
} renderable_t;

/**
 * @brief A camera_t contains the projection and view matrices for a camera as well as the fields required for
 * creating those matrices.
 * 
 */
typedef struct {
  mat4 projection_matrix;   // The projection matrix to be sent to the GPU. Will be set to a perspective mode.
  mat4 view_matrix;         // The view matrix to be sent to the GPU for representing the camera's orientation.
  
  /**
   * @brief Parameters for building a projection matrix
   * 
   */
  struct {
    float fov;      // The field of view
    float aspect;   // The aspect ratio
    float z_near;     // The near z clipping plane
    float z_far;      // The far z clipping plane
  } proj_fields;

  /**
   * @brief Parameters for building a view matrix
   * 
   */
  struct {
    vec3 position;  // The position of the camera
    vec3 at;        // The position of the object to look at
    vec3 up;        // The up vector for orienting the camera
  } view_fields;
} camera_t;


// DATA //




// FUNCTIONS //

// SHADER FUNCTIONS //

/**
 * @brief Compiles and links a usable shader program
 * 
 * @param vertex_shader_path    Path to the vertex shader program on disk
 * @param fragment_shader_path  Path to the fragment shader program on disk
 * @return GLuint   The id of the shader program
 */
extern GLuint compileAndLinkShaderProgram(const char *vertex_shader_path, const char *fragment_shader_path);

/**
 * @brief Send a vec4 to a uniform in a given shader program
 * 
 * @param program
 * @param uniform_name 
 * @param vector 
 */
extern void setUniformVec4(GLuint program, const char *uniform_name, vec4 vector);

/**
 * @brief Send a mat4 to a uniform in a given shader program
 * 
 * @param program
 * @param uniform_name 
 * @param matrix 
 */
extern void setUniformMat4(GLuint program, const char *uniform_name, mat4 matrix);

// TEXTURE FUNCTIONS //

/**
 * @brief Create a Texture2D From Image object
 * 
 * @param filepath 
 * @param wrap_s 
 * @param wrap_t 
 * @param min_filter 
 * @param mag_filter 
 * @return texture_t 
 */
extern texture_t createTexture2DFromImage(
  const char *filepath, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter);

// MESH FUNCTIONS //

/**
 * @brief Build a mesh_t object in the shape of a sphere with given radius, stacks,
 * and sectors
 * 
 * @param radius    The radius of the sphere
 * @param stacks    The number of vertical strips from the top pole to the bottom pole
 * @param sectors   The number of horizontal strips along the side of the sphere
 * @return mesh_t 
 */
extern mesh_t buildSphereMesh(GLfloat radius, GLuint stacks, GLuint sectors);

/**
 * @brief Build a mesh_t object in the shape of an icosphere with given radius and subdivisions
 * 
 * @param radius        The radius of the icosphere
 * @param subdivisions  The number of subdivisions
 * @return mesh_t       A mesh_t object containing the icosphere geometry
 */
extern mesh_t buildIcosphereMesh(GLfloat radius, GLuint subdivisions);

/**
 * @brief Free the memory for a mesh_t object, removing the data from VRAM.
 * 
 * @param mesh 
 */
extern void freeMesh(mesh_t *mesh);

// RENDERABLE FUNCTIONS //


// CAMERA FUNCTIONS //

/**
 * @brief Build a new camera object
 * 
 * @param fov           The field of view of the camera
 * @param aspect        The aspect ratio of the screen
 * @param z_near         The near z-clipping plane
 * @param z_far          The far z-clipping plane
 * @param position      The position of the camera
 * @param at            The position to look at
 * @param up            The up vector to orient the camera by
 * @return camera_t 
 */
extern camera_t buildCamera(float fov, float aspect, float z_near, float z_far, vec3 position, vec3 at, vec3 up);

#endif