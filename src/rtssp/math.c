/**
 * @file math.c
 * @author Joseph St. Pierre
 * @brief 
 * @version 0.1
 * @date 2019-11-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */


// INCLUDES //

#include "rtssp/math.h"

#include <assert.h>


// FUNCTIONS //

highp_vec3 addHighPVectors(highp_vec3 v1, highp_vec3 v2) {
  highp_vec3 result;

  result.x = v1.x + v2.x;
  result.y = v1.y + v2.y;
  result.z = v1.z + v2.z;

  return result;
}

highp_vec3 subtractHighPVectors(highp_vec3 v1, highp_vec3 v2) {
  highp_vec3 result;

  result.x = v1.x - v2.x;
  result.y = v1.y - v2.y;
  result.z = v1.z - v2.z;

  return result;
}

highp_vec3 scaleHighPVector(highp_vec3 v, double scale) {
  highp_vec3 result;

  result.x = v.x * scale;
  result.y = v.y * scale;
  result.z = v.z * scale;

  return result;
}

void convertHighPVector(const highp_vec3 *src, vec3 dest, float scale_factor) {
  assert (src && dest && scale_factor >= 1.0f);

  // Reduce down to dest using scale factor
  dest[0] = src->x / scale_factor;
  dest[1] = src->y / scale_factor;
  dest[2] = src->z / scale_factor;
}