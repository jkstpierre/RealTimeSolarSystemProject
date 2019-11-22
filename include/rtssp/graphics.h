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


// DATA //




// FUNCTIONS //

// SHADER FUNCTIONS //

/**
 * @brief Compiles a shader program from disk and returns a handle to it
 * 
 * @param shader_path   Path to the shader program on disk
 * @param type          The type of shader to compile
 * @return GLuint       Handle to the shader
 */
extern GLuint compileShader(const char *shader_path, GLenum type);

/**
 * @brief Compile and links a usable shader program
 * 
 * @param vertex_shader_path    Path to the vertex shader program on disk
 * @param fragment_shader_path  Path to the fragment shader program on disk
 * @param geometry_shader_path  Path to the optional geometry shader program on disk
 * @return GLuint   The id of the shader program
 */
extern GLuint compileAndLinkShaderPrograms(
  const char *vertex_shader_path, const char *fragment_shader_path, const char *geometry_shader_path);

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



#endif