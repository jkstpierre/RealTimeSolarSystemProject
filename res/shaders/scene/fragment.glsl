/*
  Scene Fragment Shader
  Author: Joseph St. Pierre
  Year: 2019
*/

#version 330 core

// Outputs
layout (location = 0) out vec4 fragment_color;

// Inputs
in vec3 f_normal;
in vec2 f_uv;

// Uniforms
uniform int use_texture;
uniform sampler2D diffuse_map;

void main() {
  // If no texture, just draw white fragments
  if (use_texture == 0)
    fragment_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  else
    fragment_color = texture(diffuse_map, f_uv);  // Sample from the diffuse_map
}
