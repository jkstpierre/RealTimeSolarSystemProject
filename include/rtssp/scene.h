/**
 * @file scene.h
 * @author Joseph St. Pierre
 * @brief 
 * @version 0.1
 * @date 2019-11-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _RTSSP_SCENE_H_
#define _RTSSP_SCENE_H_


// INCLUDES //

#include "rtssp/graphics.h"
#include "rtssp/math.h"


// DEFINITIONS //

#define DEFAULT_CAMERA_FOV      45.0f
#define DEFAULT_CAMERA_Z_NEAR   0.1f
#define DEFAULT_CAMERA_Z_FAR    10000000.0f

#define SCENE_VERTEX_SHADER_DIR     "../res/shaders/scene/vertex.glsl"
#define SCENE_FRAGMENT_SHADER_DIR   "../res/shaders/scene/fragment.glsl"


// STRUCTS //

/**
 * @brief A phys_object_t is any object that appears in our solar system whether it be a planet or a moon or the sun.
 * 
 */
typedef struct {
  renderable_t renderable;    // The renderable component (contains all the data for OpenGL to draw the phys_object_t)
  highp_vec3 position;        // The position of the phys_object_t in high precision
  highp_vec3 rotation;        // The rotation of the phys_object in high precision
  double mass;                // The mass of the object
} phys_object_t;


// DATA //

// CAMERA //

extern camera_t camera;   // The camera for the scene

// PHYSICS OBJECTS //

extern phys_object_t sol;   // The sun


// FUNCTIONS //

// PHYSICS OBJECT FUNCTIONS //

/**
 * @brief Build a physics object with a given mesh and texture, 
 * starting position, starting rotation, scale, and mass
 * 
 * @param mesh
 * @param texture
 * @param position 
 * @param rotation 
 * @param scale
 * @param mass 
 * @return phys_object_t 
 */
extern phys_object_t buildPhysicsObject(
  mesh_t mesh, texture_t texture, highp_vec3 position, highp_vec3 rotation, highp_vec3 scale, double mass);

// SCENE  FUNCTIONS //

/**
 * @brief Initialize the scene
 * 
 */
extern void initScene(void);

/**
 * @brief Update the scene using delta time
 * 
 * @param dt 
 */
extern void updateScene(float dt);

/**
 * @brief Draw a renderable to the active framebuffer and handle interpolation. This function
 * assumes a valid vao and shader are active and that the renderable's vbo has been setup with the
 * active vao.
 * 
 * @param renderable 
 * @param alpha 
 */
extern void drawRenderable(renderable_t renderable, float alpha);

/**
 * @brief Draw the scene to the screen using alpha interpolation
 * 
 * @param alpha 
 */
extern void drawScene(float alpha);

/**
 * @brief Free the resources for the scene
 * 
 */
extern void freeScene(void);

#endif