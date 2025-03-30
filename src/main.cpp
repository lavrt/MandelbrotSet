#include "common.h"
#include "defaultRender.h"
#include "vectorizedRender.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set");
    sf::Uint8* pixels = new sf::Uint8[WIDTH * HEIGHT * 4];

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    texture.update(pixels);

    sf::Sprite sprite(texture);

    sf::Font font;
    font.loadFromFile("./resources/arial.ttf");
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition(10, 10);

    sf::Clock clock;
    while (window.isOpen()) {      
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } 
        }

        float fps = 1.0 / clock.restart().asSeconds();
        fpsText.setString("FPS: " + std::to_string((int)fps));

        VectorizedRender(pixels);

        texture.update(pixels);
        window.clear();
        window.draw(sprite);
        window.draw(fpsText);
        window.display();
    }
    
    delete[] pixels;
    return 0;
}



