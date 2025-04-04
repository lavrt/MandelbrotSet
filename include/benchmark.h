#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <SFML/Graphics.hpp>
#include "common.h"

const size_t FRAME_COUNT = 10;

#define STRINGIFY(x_) #x_

void PerformanceTest(void (*RenderMandelbrot)(sf::Uint8*, tParametrs), sf::Uint8* pixels, tParametrs position);

#endif // BENCHMARK_H