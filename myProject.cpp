#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Automata.h"



using namespace std;

int main()
{
    Automata Sandbox;

    sf::RenderWindow screen(sf::VideoMode(1000,1000),"AUTOMATON");
    screen.setFramerateLimit(60);
    screen.setPosition({1500,1000});

    sf::Event e;

    while (screen.isOpen())
    {

        while(screen.pollEvent(e))
        {
            if (e.type==sf::Event::Closed)
                screen.close();

        }


        screen.clear(sf::Color::Black); //clear to black

        Sandbox.update(screen);
        Sandbox.draw(screen);  //send window handle to class





        screen.display();




    }



    cout<<"Hello World..."<<endl;

    return 0;
    
}