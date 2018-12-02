/* to compile:
 *
 * Download and install sfml:
 * sudo apt-get install libsfml-dev in terminal
 * 
 * 
 * 1) compile this source, g++ -c main.cpp
 * 2) g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
 * 3) execute ./sfml-app
 */

#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
