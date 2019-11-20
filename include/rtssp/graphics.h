/**
 * @file graphics.h
 * @author Joseph St. Pierre
 * @brief 
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
 * @brief A mesh_t contains all the data required for drawing a piece of geometry using
 * OpenGL
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
 * @brief 
 * 
 */
typedef struct {

} renderable_t;

#endif