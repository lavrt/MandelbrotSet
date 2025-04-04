#ifndef ARRAYED_RENDER_H
#define ARRAYED_RENDER_H

#include <SFML/Graphics.hpp>
#include "common.h"

#define FOR_EACH_COORDINATE for (size_t i = 0; i < VECTOR_SIZE; i++)

#define VECTOR_SIZE 8 

void ArrayedRender(sf::Uint8* pixels, tParametrs position);

#endif // ARRAYED_RENDER_H