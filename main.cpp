#include <SFML/Window.hpp>
#include <conio.h>
int main()
{
    sf::Window window;
    window.create(sf::VideoMode(800, 600), "My window");
    _getch();
    return 0;
}