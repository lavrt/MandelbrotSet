#include "defaultRender.h"

// static ------------------------------------------------------------------------------------------

static void FillPixelArray(sf::Uint8* pixels, size_t x, size_t y, size_t iter);

// global ------------------------------------------------------------------------------------------

void DefaultRender(sf::Uint8* pixels, tParametrs position) {
    float pX = INIT_X + position.offsetX;
    float pY = INIT_Y + position.offsetY;

    float stepX = (4. / WIDTH * ASPECT) / position.zoom;
    float stepY = (4. / HEIGHT) / position.zoom;

    for (size_t y = 0; y < HEIGHT; y++) {
        pY += stepY;
        for (size_t x = 0; x < WIDTH; x++) {
            pX += stepX;
            
            float sX = 0;
            float sY = 0;
            float sX2 = 0;
            float sY2 = 0;

            size_t iter = 0;
            for (; sX2 + sY2 < MAX_RADIUS * MAX_RADIUS && iter < MAX_ITER; iter++) {
                sY = 2 * sX * sY + pY;
                sX = sX2 - sY2 + pX;

                sX2 = sX * sX;
                sY2 = sY * sY; 
            }
            
            FillPixelArray(pixels, x, y, iter);
        }
        pX = INIT_X + position.offsetX;
    }
}

// static ------------------------------------------------------------------------------------------

static void FillPixelArray(sf::Uint8* pixels, size_t x, size_t y, size_t iter) {
    uint8_t r = 0, g = 0, b = 0;

    if (iter < MAX_ITER) {
        float t = (float)iter / MAX_ITER;
        r = 9 * t * 255;
        g = 5 * t * 255;
        b = 8 * t * 255;
    }
    
    size_t pixelIndex = (x + y * WIDTH) * 4;
    pixels[pixelIndex] = r;
    pixels[pixelIndex + 1] = g;
    pixels[pixelIndex + 2] = b;
    pixels[pixelIndex + 3] = 255;
}
