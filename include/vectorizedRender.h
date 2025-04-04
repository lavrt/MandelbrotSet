#ifndef VECTORIZED_RENDER_H
#define VECTORIZED_RENDER_H

#include <SFML/Graphics.hpp>
#include <immintrin.h>
#include "common.h"

const __m256 _zero_ = _mm256_set1_ps(0);
const __m256 _one_  = _mm256_set1_ps(1);
const __m256 _two_  = _mm256_set1_ps(2); 
const __m256 _255_ = _mm256_set1_ps(255);
const __m256 _redMultiplier_ = _mm256_set1_ps(9 * 255);
const __m256 _greenMultiplier_ = _mm256_set1_ps(5 * 255);
const __m256 _blueMultiplier_ = _mm256_set1_ps(8 * 255);

const __m256 _maxRadius2_ = _mm256_set1_ps(MAX_RADIUS * MAX_RADIUS);
const __m256 _maxIter_ = _mm256_set1_ps(MAX_ITER);

void VectorizedRender(sf::Uint8* pixels, tParametrs position);

#endif // VECTORIZED_RENDER_H