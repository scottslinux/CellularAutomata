#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace std;

class Automata
{
    private:

    const float ScreenWidth=1000;   //size of the graphicss window (probably in main....
    const int celldimension=25;
    float cellside; // pix dimension of individual cell
    int totalcells;

    int cellx=0;
    int celly=0;

    

    enum class cellint{empty, sand, rock, water};   //create the potential cell states
    cellint cellstate;

    vector<cellint> Grid;   //the world!!!!

    sf::Vector2f rowcol{0,0};   //use to retrieve position



    public:

    sf::RectangleShape baserect;
    sf::RectangleShape solid;

    
    
    sf::Texture grainTex;
    sf::Sprite specSprite;



    Automata();
    ~Automata();

    void update(sf::RenderWindow* window);
    void draw(sf::RenderWindow* window);
    void drawGrid(sf::RenderWindow* window);   //pass the side dimension of the square and draw the grid
    void mouseAction(sf::RenderWindow* window);         //allow user input for element design
    void iterator();            //Magic time!
    int gridXY2index(sf::Vector2f gridXY);          //convert grid[member]-->col,row x,y
    sf::Vector2i index2GridXY(int index);








};