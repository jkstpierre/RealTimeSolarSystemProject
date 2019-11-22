/*
  Scene Vertex Shader
  Author: Joseph St. Pierre
  Year: 2019
*/

#version 330 core

// Inputs
layout (location = 0) in vec3 position;   // The vertex position
layout (location = 1) in vec3 normal;     // The vertex normal
layout (location = 2) in vec2 uv;         // The vertex texture coords

// Outputs
out vec3 f_normal;    // Output fragment normal vector
out vec2 f_uv;        // Output fragment texture coords

// Uniforms
uniform mat4 MVP;   // The model-view-projection matrix

void main() {
  gl_Position = MVP * position;   // Compute the vertex position

  // Forward normal vector and uv coords to the fragment shader
  f_normal = normal
  f_uv = uv;
}