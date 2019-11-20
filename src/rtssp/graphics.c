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


// FUNCTIONS //

mesh_t buildSphereMesh(GLfloat radius, GLuint sectors, GLuint stacks) {
  
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