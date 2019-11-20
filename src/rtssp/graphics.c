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


// FUNCTIONS //

mesh_t buildSphereMesh(GLfloat radius, GLuint sectors, GLuint stacks) {
  // Fields
  mesh_t sphere;  // The mesh we are going to return
  vertex_t *vertex_array = NULL;  // The vertex array to build

  // Compute the number of vertices to appear in the sphere
  sphere.vertex_count = (stacks + 1) * (sectors + 1);
  
  // Allocate memory for the vertex array
  vertex_array = (vertex_t *)malloc(sizeof(vertex_t) * sphere.vertex_count);

  // Temp variables for constructing the sphere
  float x, y, z, xy;  // Vertex position
  float nx, ny, nz, length_inv = 1.0f / radius;  // Vertex normal
  float u, v; // Vertex tex coords
  float sector_step = 2 * CGLM_PI / sectors; 
  float stack_step = CGLM_PI / stacks;
  float sector_angle, stack_angle;

  /*
    TODO: Finish Sphere construction here
  */

  sphere.draw_mode = GL_TRIANGLES;  // Set draw mode to triangles

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