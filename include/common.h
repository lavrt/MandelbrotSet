#ifndef COMMON_H
#define COMMON_H

struct tParametrs {
    float zoom;
    float offsetX;
    float offsetY;
};

const int WIDTH = 1920;
const int HEIGHT = 1080;
const char* const WINDOW_NAME = "Mandelbrot set";
const char* const PATH_TO_FONT = "./resources/arial.ttf";

const float ASPECT = (float)WIDTH / HEIGHT;
const float INIT_X = -2.4;
const float INIT_Y = -1.2;

const float ZOOM_MULTIPLIER = 1.2;
const float OFFSET_MULTIPLIER = 0.2;

const int MAX_ITER = 256;
const float MAX_RADIUS = 2;

#endif // COMMON_H