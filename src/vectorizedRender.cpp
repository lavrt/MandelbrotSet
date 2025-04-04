#include "vectorizedRender.h"

// static ------------------------------------------------------------------------------------------

static void FillPixelArray(sf::Uint8* pixels, size_t x, size_t y, __m256 _iter_);

static volatile int dummy = 0;

// global ------------------------------------------------------------------------------------------

void VectorizedRender(sf::Uint8* pixels, tParametrs position) {
    float pX = INIT_X + position.offsetX;
    float pY = INIT_Y + position.offsetY;

    float stepX = (4. / WIDTH * ASPECT) / position.zoom;
    float stepY = (4. / HEIGHT) / position.zoom;

    for (size_t y = 0; y < HEIGHT; y++) {
        __m256 _pY_ = _mm256_set1_ps(pY);
        pY += stepY;
        for (size_t x = 0; x < WIDTH; x += 8) {
            __m256 _offsets_ = _mm256_setr_ps(0, 1, 2, 3, 4, 5, 6, 7);
            __m256 _pX_ = _mm256_add_ps(_mm256_set1_ps(pX), _mm256_mul_ps(_offsets_, _mm256_set1_ps(stepX)));
            
            pX += 8 * stepX;

            __m256 _sX_ = _mm256_setzero_ps(); 
            __m256 _sY_ = _mm256_setzero_ps();
            __m256 _sX2_ = _mm256_setzero_ps();
            __m256 _sY2_ = _mm256_setzero_ps();

            __m256 _iter_ = _mm256_setzero_ps();

            __m256 _condition_ = _mm256_set1_ps(-1);
            while (_mm256_movemask_ps(_condition_)) {
                _sY_ = _mm256_add_ps(_mm256_mul_ps(_mm256_mul_ps(_sX_, _sY_), _two_), _pY_);
                _sX_ = _mm256_add_ps(_mm256_sub_ps(_sX2_, _sY2_), _pX_);
                _sX2_ = _mm256_mul_ps(_sX_, _sX_); 
                _sY2_ = _mm256_mul_ps(_sY_, _sY_);
            
                __m256 _condition1_ = _mm256_cmp_ps(_mm256_add_ps(_sX2_, _sY2_), _maxRadius2_, _CMP_LT_OQ);
                __m256 _condition2_ = _mm256_cmp_ps(_iter_, _maxIter_, _CMP_LT_OQ);
                _condition_ = _mm256_and_ps(_condition1_, _condition2_);
            
                _iter_ = _mm256_add_ps(_iter_, _mm256_and_ps(_condition_, _one_));

                dummy = 1;
            }
            #if defined(GRAPHICS)
                FillPixelArray(pixels, x, y, _iter_);
            #endif
        }
        pX = INIT_X + position.offsetX; 
    }
}

// static ------------------------------------------------------------------------------------------

static void FillPixelArray(sf::Uint8* pixels, size_t x, size_t y, __m256 _iter_) {
    float iters[8];
    _mm256_storeu_ps(iters, _iter_);

    for (size_t i = 0; i < 8; i++) {
        uint8_t r = 0, g = 0, b = 0;
        if ((int)iters[i] < MAX_ITER) {
            float t = iters[i] / MAX_ITER;
            r = 9 * t * 255;
            g = 5 * t * 255;
            b = 8 * t * 255;
        }
        size_t pixelIndex = (x + i + y * WIDTH) * 4;
        pixels[pixelIndex] = r;
        pixels[pixelIndex + 1] = g;
        pixels[pixelIndex + 2] = b;
        pixels[pixelIndex + 3] = 255;
    }
}