
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "Automata.h"


Automata::Automata()
{
    totalcells=celldimension*celldimension;
    Grid.resize(totalcells,cellint::empty);  //create the grid initially empty

    if(!grainTex.loadFromFile("./resources/sand.png"))
        cout<<"Texture failed to load\n";
            else    
                cout<<"Texture loaded successfully...\n";

    specSprite.setTexture(grainTex);    //place sand grain image in sprite

    cellside=ScreenWidth/celldimension;   //side dimension of individual cell...they are square

    baserect.setSize({cellside,cellside});
    baserect.setFillColor(sf::Color::Transparent);
    baserect.setOutlineColor(sf::Color::Green);
    baserect.setOutlineThickness(0);

    solid.setSize({cellside,cellside});
    solid.setFillColor(sf::Color(0,200,100,100));
    solid.setOutlineColor(sf::Color(255,0,0,100));
    solid.setOutlineThickness(0);

    

   // cout<<"Screenwidth: "<<ScreenWidth<<" celldimension: "<<celldimension<<" Cellside: "<<cellside<<endl;




}
//================================================
void Automata::update(sf::RenderWindow& window)
{
    

    mouseAction(window);
    iterator();

    
}

//================================================
void Automata::draw(sf::RenderWindow& window)
{
    drawGrid(window);


    

}


//================================================

Automata::~Automata()
{


}
//================================================
void Automata::drawGrid(sf::RenderWindow& window)
{

 /*  for (int y=0;y<celldimension;y++)     // draws the raw grid which is immediately covered by solid rec with outline
        for (int x=0;x<celldimension;x++)
            {
                baserect.setPosition({x*cellside,y*cellside});
                baserect.setOutlineColor(sf::Color(255,0,0,255));
                window.draw(baserect);
                


            }
*/
    

    for(int i=0;i<totalcells;i++)   //iterate and color the cells appropriately
    {
        
        // the *cellside converts cellxy to physical screen loction

        int gridx=index2GridXY(i).x*cellside;
        int gridy=index2GridXY(i).y*cellside;

        

        solid.setPosition({gridx, gridy});


        switch(Grid[i])
        {
            case (cellint::empty):
            {   
                solid.setFillColor(sf::Color::Black);
                break;
            }
            case (cellint::sand):
            {
                solid.setFillColor(sf::Color(168,127,80,255));
                break;
            }
            case (cellint::rock):
            {
                solid.setFillColor(sf::Color(01,82,94,255));
                break;
            }
            default:
                break;
        }

        window.draw(solid);    

    }

    return;

}
//================================================
void Automata::mouseAction(sf::RenderWindow& window)
{
    sf::Vector2i mousepos=sf::Mouse::getPosition(window);

    cellx=(int)(mousepos.x/cellside);   //was creating mouse cursor ?needed
    celly=(int) (mousepos.y/cellside);

   // solid.setPosition({cellx*cellside,celly*cellside});

    
    int gridmember=gridXY2index({cellx,celly});

   
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)&&Grid[gridmember]!=cellint::rock)
    {
       Grid[gridmember]=cellint::sand;


    }
       
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
        Grid[gridmember]=cellint::empty;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)&&Grid[gridmember]==cellint::empty)
        Grid[gridmember]=cellint::rock;


   
}
//================================================
void Automata::iterator()
{   
    //iterate from the top row to the top
    for (int y = celldimension - 1; y >= 0; --y)
        for (int x=0;x<celldimension;x++)
        {


            if(Grid[gridXY2index({x,y})]==cellint::sand&& (y!=celldimension-1)&&
                    Grid[gridXY2index({x,y+1})]!=cellint::sand&&
                    Grid[gridXY2index({x,y+1})]!=cellint::rock)  //convert xy to index and check contents
                {
                    Grid[gridXY2index({x,y})]=cellint::empty;
                    Grid[gridXY2index({x,y+1})]=cellint::sand;  //drop down one
                    continue;
                }
                else
                    if(Grid[gridXY2index({x,y})]==cellint::sand&& (y!=celldimension-1)&&
                    Grid[gridXY2index({x-1,y+1})]!=cellint::sand&&
                    Grid[gridXY2index({x,y+1})]!=cellint::rock)  //convert xy to index and check contents
                        {
                            Grid[gridXY2index({x,y})]=cellint::empty;
                            Grid[gridXY2index({x-1,y+1})]=cellint::sand;  //drop down one
                            continue;
                        }
                    else
                        if(Grid[gridXY2index({x,y})]==cellint::sand&& (y!=celldimension-1)&&
                            Grid[gridXY2index({x+1,y+1})]!=cellint::sand&&
                            Grid[gridXY2index({x,y+1})]!=cellint::rock)  //convert xy to index and check contents
                            {
                                Grid[gridXY2index({x,y})]=cellint::empty;
                                Grid[gridXY2index({x+1,y+1})]=cellint::sand;  //drop down one
                                continue;
                            }

        

        }




}
//================================================
// ⁡⁣⁢⁣​‌‍‌⁡⁣⁢⁣​‌‍‌𝗖𝗮𝗹𝗰𝘂𝗹𝗮𝘁𝗲 𝘁𝗵𝗲 𝗶𝗻𝗱𝗲𝘅 𝗳𝗿𝗼𝗺 𝗴𝗿𝗶𝗱 𝘅,𝘆​⁡

int Automata::gridXY2index(sf::Vector2f gridXY)
{

    int gridmember=gridXY.y*celldimension+ gridXY.x;

    return {gridmember};

}
//================================================
// ⁡⁣⁢⁣​‌‍‌𝗖𝗮𝗹𝗰𝘂𝗹𝗮𝘁𝗲 𝗴𝗿𝗶𝗱 𝘅,𝘆 𝗳𝗿𝗼𝗺 𝘁𝗵𝗲 𝗶𝗻𝗱𝗲𝘅​⁡

sf::Vector2i Automata::index2GridXY(int index)
{
    int gridx=(index%celldimension);
    int gridy=(index/celldimension);
    sf::Vector2i xy={gridx,gridy};
    return(xy);
}
