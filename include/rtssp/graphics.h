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

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_


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
  GLuint texture;       // The texture of the renderable
} renderable_t;


// DATA //




// FUNCTIONS //

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
 * @brief Free the memory for a mesh_t object, removing the data from VRAM.
 * 
 * @param mesh 
 */
extern void freeMesh(mesh_t *mesh);

#endif