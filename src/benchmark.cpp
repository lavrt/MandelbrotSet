#include "benchmark.h"

#include <x86intrin.h>
#include <stdlib.h>
#include <assert.h>

static void TicksDump(unsigned long long* ticks);

void PerformanceTest(void (*RenderMandelbrot)(sf::Uint8*, tParametrs), sf::Uint8* pixels, tParametrs position) {
    unsigned long long* ticks = (unsigned long long*)calloc(FRAME_COUNT, sizeof(unsigned long long));
    assert(ticks);

    unsigned aux = 0;
    for (size_t i = 0; i < FRAME_COUNT; i++) {
        unsigned long long start = __rdtscp(&aux);
        RenderMandelbrot(pixels, position);
        unsigned long long end = __rdtscp(&aux);

        ticks[i] = end - start;
    }

    TicksDump(ticks);
    free(ticks);
}

static void TicksDump(unsigned long long* ticks) {
    FILE* tickFile = fopen("./tests/tests.txt", "a+"); 
    assert(tickFile);

    //---------------------------------------------------
    #if defined(DEFAULT_RENDER)
        fprintf(tickFile, "%s ", "default_render");
    #elif defined(ARRAYED_RENDER)
        fprintf(tickFile, "%s ", "arrayed_render");
    #elif defined(VECTORIZED_RENDER)
        fprintf(tickFile, "%s ", "vectorized_render");
    #else
        fprintf(tickFile, "%s ", "default_render");
    #endif
    //---------------------------------------------------

    fprintf(tickFile, "frame_count=%lu ", FRAME_COUNT);

    //---------------------------------------------------
    #if defined(GCC)
        fprintf(tickFile, "%s ", "gcc");
    #elif defined(GPP)
        fprintf(tickFile, "%s ", "g++");
    #elif defined(CLANG)
        fprintf(tickFile, "%s ", "clang");
    #else 
        fprintf(tickFile, "%s ", "g++");
    #endif
    //---------------------------------------------------

    //---------------------------------------------------
    #if defined(O1)
        fprintf(tickFile, "%s ", "-O1");
    #elif defined(O2)
        fprintf(tickFile, "%s ", "-O2");
    #elif defined(O3)
        fprintf(tickFile, "%s ", "-O3");
    #endif
    //---------------------------------------------------

    fprintf(tickFile, "\n");

    for (size_t i = 0; i < FRAME_COUNT; i++) {
        fprintf(tickFile, "%llu\n", ticks[i]);
    }

    fprintf(tickFile, "\n");

    fclose(tickFile);
}