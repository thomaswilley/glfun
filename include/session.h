/*
 * Sesssion management
 * (c) @thomaswilley 2019-20
 */

#ifndef SESSION_H
#define SESSION_H

#include <stdlib.h>

typedef struct session
{
  float acceleration;
  float x_speed, y_speed, z_speed;
  float base_speed;
} Session_t;

#endif /* SESSION_H */
