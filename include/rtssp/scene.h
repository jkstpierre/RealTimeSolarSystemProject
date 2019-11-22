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


// DATA //

extern GLuint vao;    // The scene vertex array object


// FUNCTIONS //

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