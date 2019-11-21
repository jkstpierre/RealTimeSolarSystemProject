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
#include <math.h>
#include <assert.h>


// FUNCTIONS //

mesh_t buildSphereMesh(GLfloat radius, GLuint stacks, GLuint sectors) {
  // Assert the inputs are in range
  assert(sectors >= 2);
  assert(stacks > 0);
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

  // Create a new VBO for the mesh
  glGenBuffers(1, &(sphere.vbo));

  // Create a new EBO for the mesh
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