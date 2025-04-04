#ifndef VECTORIZED_RENDER_H
#define VECTORIZED_RENDER_H

#include <immintrin.h>
#include "common.h"

const __m256 _zero_ = _mm256_set1_ps(0.0f);
const __m256 _one_  = _mm256_set1_ps(1.0f);
const __m256 _two_  = _mm256_set1_ps(2.0f); 
const __m256 _255_ = _mm256_set1_ps(255.0f);
const __m256 _redMultiplier_ = _mm256_set1_ps(9.0f * 255.0f);
const __m256 _greenMultiplier_ = _mm256_set1_ps(5.0f * 255.0f);
const __m256 _blueMultiplier_ = _mm256_set1_ps(8.0f * 255.0f);

const __m256 _maxRadius2_ = _mm256_set1_ps(MAX_RADIUS * MAX_RADIUS);
const __m256 _maxIter_ = _mm256_set1_ps(MAX_ITER);

void VectorizedRender(sf::Uint8* pixels, tParametrs position);

#endif // VECTORIZED_RENDER_H