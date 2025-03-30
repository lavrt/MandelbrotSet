#include "defaultRender.h"

void DefaultRender(sf::Uint8* pixels) {
    float pX = INIT_X + offsetX;
    float pY = INIT_Y + offsetY;

    float stepX = (4. / WIDTH * ASPECT) / zoom;
    float stepY = (4. / HEIGHT) / zoom;

    for (size_t y = 0; y < HEIGHT; y++) {
        pY += stepY;
        for (size_t x = 0; x < WIDTH; x++) {
            pX += stepX;
            
            float sX = 0, sX2 = 0;
            float sY = 0, sY2 = 0;

            size_t iter = 0;
            for (; sX2 + sY2 < MAX_RADIUS * MAX_RADIUS && iter < MAX_ITER; iter++) {
                    sY = 2 * sX * sY + pY;
                    sX = sX2 - sY2 + pX;

                    sX2 = sX * sX;
                    sY2 = sY * sY; 
                }
            
            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;

            if (iter < MAX_ITER) {
                float t = (float)iter / MAX_ITER;
                r = 9 * (1-t) * t * t * 255;
                g = 5 * (1-t) * (1-t) * t * 255;
                b = 8 * (1-t) * (1-t) * t * 255;
            }
                
            pixels[(x + y * WIDTH) * 4]     = r;
            pixels[(x + y * WIDTH) * 4 + 1] = g;
            pixels[(x + y * WIDTH) * 4 + 2] = b;
            pixels[(x + y * WIDTH) * 4 + 3] = 255;
        }
        pX = INIT_X + offsetX;
    }
}