#include "arrayedRender.h"

// static ------------------------------------------------------------------------------------------

static void FillPixelArray(sf::Uint8* pixels, size_t x, size_t y, float* _iter_);

static volatile int dummy = 0;

// global ------------------------------------------------------------------------------------------

void ArrayedRender(sf::Uint8* pixels, tParametrs position) {
    float _maxRadius_[VECTOR_SIZE] = {};
    float _maxIter_[VECTOR_SIZE] = {};

    FOR_EACH_COORDINATE _maxRadius_[i] = MAX_RADIUS;
    FOR_EACH_COORDINATE _maxIter_[i] = MAX_ITER;

    float pX = INIT_X + position.offsetX;
    float pY = INIT_Y + position.offsetY;

    float stepX = (4. / WIDTH * ASPECT) / position.zoom;
    float stepY = (4. / HEIGHT) / position.zoom;

    for (size_t y = 0; y < HEIGHT; y++) {
        float _pY_[VECTOR_SIZE] = {};
        FOR_EACH_COORDINATE _pY_[i] = pY;
        pY += stepY;

        for (size_t x = 0; x < WIDTH; x += VECTOR_SIZE) {
            float _pX_[VECTOR_SIZE] = {};
            FOR_EACH_COORDINATE _pX_[i] = pX + i * stepX;
            pX += VECTOR_SIZE * stepX;

            float _sX_[VECTOR_SIZE] = {};    
            float _sY_[VECTOR_SIZE] = {};    
            float _sX2_[VECTOR_SIZE] = {};    
            float _sY2_[VECTOR_SIZE] = {};    

            float _iter_[VECTOR_SIZE] = {};

            bool nonZeroConditionArray = false;
            do {
                _sY_[VECTOR_SIZE] = {};
                _sX_[VECTOR_SIZE] = {};
                _sY2_[VECTOR_SIZE] = {};
                _sX2_[VECTOR_SIZE] = {};

                FOR_EACH_COORDINATE _sY_[i] = 2 * _sX_[i] * _sY_[i] + _pY_[i];
                FOR_EACH_COORDINATE _sX_[i] = _sX2_[i] - _sY2_[i] + _pX_[i];
                FOR_EACH_COORDINATE _sX2_[i] = _sX_[i] * _sX_[i];
                FOR_EACH_COORDINATE _sY2_[i] = _sY_[i] * _sY_[i];

                float _condition1_[VECTOR_SIZE] = {};
                float _condition2_[VECTOR_SIZE] = {};
                float _condition_[VECTOR_SIZE] = {};

                FOR_EACH_COORDINATE _condition1_[i] = _sX2_[i] + _sY2_[i] < _maxRadius_[i] * _maxRadius_[i];
                FOR_EACH_COORDINATE _condition2_[i] = _iter_[i] < _maxIter_[i];
                FOR_EACH_COORDINATE _condition_[i] = _condition1_[i] * _condition2_[i];

                FOR_EACH_COORDINATE _iter_[i] += _condition_[i];

                nonZeroConditionArray = false;
                FOR_EACH_COORDINATE if (_condition_[i]) { nonZeroConditionArray = true; break; }

                dummy = 1;
            } while (nonZeroConditionArray);

            #if defined(GRAPHICS)
                FillPixelArray(pixels, x, y, _iter_);
            #endif
        }
        pX = INIT_X + position.offsetX; 
    }
}

// static ------------------------------------------------------------------------------------------

static void FillPixelArray(sf::Uint8* pixels, size_t x, size_t y, float* _iter_) {
    FOR_EACH_COORDINATE {
        uint8_t r = 0, g = 0, b = 0;
        if (_iter_[i] < MAX_ITER) {
            float t = _iter_[i] / MAX_ITER;
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
