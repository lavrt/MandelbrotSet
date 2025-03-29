#include <stdio.h>
#include <math.h>
#include <SFML/Graphics.hpp>

const int WIDTH = 1920;
const int HEIGHT = 1080;
const double ASPECT = (double)WIDTH / HEIGHT;
const double INIT_X = -2.4;
const double INIT_Y = -1.2;

const int MAX_ITER = 256;
const double MAX_RADIUS = 2;

double zoom = 1.7;
double offsetX = 0;
double offsetY = 0;

void DisplayMandelbrotSet(sf::Uint8* pixels);

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set");
    sf::Uint8* pixels = new sf::Uint8[WIDTH * HEIGHT * 4];

    DisplayMandelbrotSet(pixels);

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    texture.update(pixels);

    sf::Sprite sprite(texture);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition(10, 10);

    sf::Clock clock;
    while (window.isOpen()) {
        float fps = 1.0f / clock.restart().asSeconds();
        fpsText.setString("FPS: " + std::to_string((int)fps));
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } 
        }

        DisplayMandelbrotSet(pixels);

        texture.update(pixels);
        window.clear();
        
        window.draw(sprite);
        window.draw(fpsText);
        window.display();
    }
    
    delete[] pixels;
    return 0;
}

void DisplayMandelbrotSet(sf::Uint8* pixels) {
    double pX = INIT_X + offsetX;
    double pY = INIT_Y + offsetY;

    double stepX = (4. / WIDTH * ASPECT) / zoom;
    double stepY = (4. / HEIGHT) / zoom;

    for (size_t y = 0; y < HEIGHT; y++) {
        pY += stepY;
        for (size_t x = 0; x < WIDTH; x++) {
            pX += stepX;
            
            double sX = 0, sX2 = 0;
            double sY = 0, sY2 = 0;

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
                iter *= sqrt(abs(sin(exp(sqrt(abs(sX+sY))))));
                double t = (double)iter / MAX_ITER;
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

