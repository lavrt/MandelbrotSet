#include "common.h"
#include "defaultRender.h"
#include "vectorizedRender.h"
#include "arrayedRender.h"

static void EventHandling(sf::RenderWindow* window, tParametrs* position);

int main() {
    tParametrs position = {1.7, 0, 0};

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), WINDOW_NAME); 
    sf::Uint8* pixels = (sf::Uint8*)calloc(WIDTH * HEIGHT * 4, sizeof(sf::Uint8)); 

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    texture.update(pixels);

    sf::Sprite sprite(texture);

    sf::Font font;
    font.loadFromFile(PATH_TO_FONT);
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition(10, 10);

    sf::Clock clock;
    while (window.isOpen()) {      
        EventHandling(&window, &position);

        // TODO считай в тактах процессора (инстуркция ассемблерная)
        float fps = 1.0 / clock.restart().asSeconds();
        fpsText.setString("FPS: " + std::to_string((int)fps));

        ArrayedRender(pixels, position);

        texture.update(pixels);
        window.clear();
        window.draw(sprite);
        window.draw(fpsText);
        window.display();
    }
    free(pixels);

    return 0;
}

static void EventHandling(sf::RenderWindow* window, tParametrs* position) { 
    sf::Event event;
    while ((*window).pollEvent(event)) { 
        if (event.type == sf::Event::Closed) {
            (*window).close();
        }

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Add:
                position->zoom *= ZOOM_MULTIPLIER;
            break;
            case sf::Keyboard::Subtract:
                position->zoom /= ZOOM_MULTIPLIER;
            break;
            case sf::Keyboard::Numpad4:
                position->offsetX -= OFFSET_MULTIPLIER / position->zoom;
            break;
            case sf::Keyboard::Numpad6:
                position->offsetX += OFFSET_MULTIPLIER / position->zoom;
            break;
            case sf::Keyboard::Numpad8:
                position->offsetY -= OFFSET_MULTIPLIER / position->zoom;
            break;
            case sf::Keyboard::Numpad2:
                position->offsetY += OFFSET_MULTIPLIER / position->zoom;
            break;
            default: break;
            }
        }
    }
}