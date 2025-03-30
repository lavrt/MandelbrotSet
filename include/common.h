#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <SFML/Graphics.hpp>

const int WIDTH = 1920;
const int HEIGHT = 1080;
const float ASPECT = (float)WIDTH / HEIGHT;
const float INIT_X = -2.4;
const float INIT_Y = -1.2;

const int MAX_ITER = 256;
const float MAX_RADIUS = 2;

const float zoom = 1.7;
const float offsetX = 0;
const float offsetY = 0;

#endif // COMMON_H