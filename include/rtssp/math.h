/**
 * @file math.h
 * @author Joseph St. Pierre
 * @brief 
 * @version 0.1
 * @date 2019-11-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _RTSSP_MATH_H_
#define _RTSSP_MATH_H_


// INCLUDES //

#include <cglm/cglm.h>


// DEFINES //

#define DEFAULT_HIGHP_TO_VEC3_SCALE_FACTOR      10000.0f    // Each unit in glm corresponds to 10000 units of highp


// STRUCTS //

/**
 * @brief Since cglm operates entirely with floats we need a new vec3 type that can store astronomical distances and scales for
 * the solar system.
 * 
 */
typedef struct {
  double x;
  double y;
  double z;
} highp_vec3;


// FUNCTIONS //

/**
 * @brief Add vectors v1 and v2 together
 * 
 * @param v1 
 * @param v2 
 * @return highp_vec3 
 */
extern highp_vec3 addHighPVectors(highp_vec3 v1, highp_vec3 v2);

/**
 * @brief Subtract vector v2 from v1
 * 
 * @param v1 
 * @param v2 
 * @return highp_vec3 
 */
extern highp_vec3 subtractHighPVectors(highp_vec3 v1, highp_vec3 v2);

/**
 * @brief Scale vector v by a given scalar
 * 
 * @param v 
 * @param scale 
 * @return highp_vec3 
 */
extern highp_vec3 scaleHighPVector(highp_vec3 v, double scale);

/**
 * @brief Converts a high precision 192 bit vector to cglm compatible 92 bit vector using a positive scale factor.
 * 
 * @param src   The high precision vector source
 * @param dest  The cglm vector destination
 * @param scale_factor  The positive scale_factor to use for conversion. Note: MUST BE >= 1
 */
extern void convertHighPVector(const highp_vec3 *src, vec3 dest, float scale_factor);

#endif