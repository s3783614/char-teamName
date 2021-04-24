
#include "Bag.h"
#include "Tile.h"
#include "TileCodes.h"
#include <fstream>

Bag::Bag()
{

}

void Bag::readAllTiles(std::string inputFileName, Tile* tileBag[])
{
    std::ifstream inputFile(inputFileName);

    // increments till the eof
    int numRead = 0;

    while(!inputFile.eof())
    {
        Colour colour = RED;
        Shape shape = CIRCLE;

        bool readColourSuccess = false;
        readColourSuccess = readColourTile(inputFile, &colour, &shape);

        bool readShapeSuccess = false;
        readShapeSuccess = readShapeTile(inputFile, &colour, &shape);
        
        bool readSuccess = false;
        if (readColourSuccess == true && readShapeSuccess == true)
        {
            readSuccess = true;
        }

        if(!inputFile.eof() && readSuccess)
        {

            Tile* tile =  new Tile(colour, shape);
            tileBag[numRead] = tile;
            numRead++;
        }
    }

    
    
    
    
}


bool Bag::readColourTile(std::ifstream& inputFile, Colour* colour, Shape* shape)
{
    // READ COLOUR
    Colour readColour = 'R';
    inputFile >> readColour;
    //might need to refactor the name a bit
    bool readColourSuccess = true;


    if(readColour == 'R')
    {
        *colour = RED;
    }
    else if(readColour == 'O')
    {
        *colour = ORANGE;
    }
    else if(readColour == 'Y')
    {
        *colour = YELLOW;
    }
    else if(readColour == 'G')
    {
        *colour = GREEN;
    }
    else if(readColour == 'B')
    {
        *colour = BLUE;
    }
    else if(readColour == 'P')
    {
        *colour = PURPLE;
    }
    else
    {
        readColourSuccess = false;

        //might be useful when we read input from user
        // std::cout << "Incorrect colour try again!" << std::endl;
        // idk..
    }
    
    inputFile >> *shape;

    

    return readColourSuccess;

}

bool Bag::readShapeTile(std::ifstream& inputFile, Colour* colour, Shape* shape)
{

    inputFile >> *colour;

    // READ SHAPE
    Shape readShape = 1;
    inputFile >> readShape;
    //might need to refactor the name a bit
    bool readShapeSuccess = true;
    
    if(readShape == 1)
    {
        *shape = CIRCLE;
    }
    else if(readShape == 2)
    {
        *shape = STAR_4;
    }
    else if(readShape == 3)
    {
        *shape = DIAMOND;
    }
    else if(readShape == 4)
    {
        *shape = SQUARE;
    }
    else if(readShape == 5)
    {
        *shape = STAR_6;
    }
    else if(readShape == 6)
    {
        *shape = CLOVER;
    }
    else
    {
        readShapeSuccess = false;

        //might be useful when we read input from user
        // std::cout << "Incorrect shape try again!" << std::endl;
        // idk..
    }

    return readShapeSuccess;
}