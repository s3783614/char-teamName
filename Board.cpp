#include "Board.h"

// Board object holds the board as a 2d Vector of tile pointers
// Size can be set at intialisation, knows if no tiles have been placed
Board::Board()
{
   theBoard.resize(NO_OF_ROWS, std::vector<Tile *>(NO_OF_COLS, nullptr));
   bag = new LinkedList();
   empty = true;
   this->row = NO_OF_ROWS;
   this->col = NO_OF_COLS;
}

Board::Board(int row, int col)
{
   theBoard.resize(NO_OF_ROWS, std::vector<Tile *>(NO_OF_COLS, nullptr));
   bag = new LinkedList();
   empty = true;
   this->row = row;
   this->col = col;
}

Board::~Board()
{
   clear();
   delete bag;
   bag = nullptr;
}

void Board::clear()
{
   for (int i = 0; i < row; i++)
   {
      for(int j = 0; j < col; j++)
      {
         Location location(i, j);
         Tile* tile = getTile(location);
         if(tile != nullptr)
         {
            delete tile;
         }
      }
   }
}

void Board::setRow(int row)
{
   this->row = row;
}

void Board::setCol(int col)
{
   this->col = col;
}

void Board::setBag(LinkedList* linkedList)
{
   bag = linkedList;
}

LinkedList *Board::getBag()
{
   return bag;
}

Tile* Board::getTile(Location location)
{
   return theBoard[location.col][location.row];
}

bool Board::isSpotTaken(Location location)
{
   // std::cout << "row: "<<row<<" col: " << col <<std::endl;
   bool check = false;
   if (theBoard[location.col][location.row] != nullptr)
   {
      check = true;
   }

   return check;
}

void Board::toString()
{
   std::string boardPrint = " ";

   // Should print 1 through 26
   for (int j = 0; j < NO_OF_COLS; j++)
   {
      if (j < 10)
      {
         boardPrint.append("  ");
      }
      else
      {
         boardPrint.append(" ");
      }

      boardPrint.append(std::to_string(j + 1));
   }
   boardPrint += "\n";

   for (int i = 0; i < (NO_OF_COLS + 1) * 3; i++)
   {
      boardPrint.append("-");
   }
   boardPrint.append("\n");
   for (int i = 0; i != NO_OF_ROWS; i++)
   {
      char letter = i + 65;
      boardPrint += letter;
      boardPrint.append(" ");
      for (int j = 0; j < NO_OF_COLS; j++)
      {
         boardPrint.append("|");

         if (theBoard[j][i] != nullptr)
         {
            std::string colour(1, theBoard[j][i]->getColour());
            boardPrint.append(colour);

            int theShape = theBoard[j][i]->getShape();
            std::string shape = std::to_string(theShape);
            boardPrint.append(shape);
         }
         else
         {
            boardPrint.append("  ");
         }
      }
      boardPrint += "|\n";
   }
   for (int i = 0; i < (NO_OF_COLS + 1) * 3; i++)
   {
      boardPrint.append("-");
   }
   std::cout << boardPrint << std::endl;
}

void Board::placeTile(Tile *newTile, Location location)
{
   theBoard[location.col][location.row] = newTile;
}

bool Board::checkEmpty()
{
   bool isEmpty = true;
   for(int row = 0; row < NO_OF_ROWS; row++)
   {
      for(int col = 0; col < NO_OF_COLS; col++)
      {
         if(theBoard[col][row] != nullptr)
         {
            isEmpty = false;
         }
      }
   }

   return isEmpty;
}

bool Board::emptyLocation(Location location)
{
   bool isEmpty = false;

   if(theBoard[location.col][location.row] == nullptr)
   {
      isEmpty = true;
   }
   return isEmpty;
}

Colour Board::checkColour(Location location)
{
   //TODO
   //WRITE CONTRACT
   return theBoard[location.col][location.row]->getColour();
}

Shape Board::checkShape(Location location)
{
   //TODO
   //WRITE CONTRACT
   return theBoard[location.col][location.row]->getShape();
}

std::string Board::saveBoard()
{
   std::string boardLocation = "";
   Location location;
   bool firstTile = true;
   for (int row = 0; row < NO_OF_ROWS; row++)
   {
      for (int col = 0; col < NO_OF_COLS; col++)
      {
         location.row = row;
         location.col = col;
         
         if(!emptyLocation(location))
         {
            if(!firstTile)
            {
               boardLocation += ", ";
               
            }
            firstTile = false;
            boardLocation += checkColour(location);
            boardLocation += std::to_string(checkShape(location));
            boardLocation += '@';
            boardLocation += row + 65;
            boardLocation += std::to_string(col + 1);
            
         }

      }
      
   }
   
   return boardLocation;

}

int Board::getRows()
{

   return row;
}

int Board::getCols()
{
   return col;
}

// Method necessary?
bool Board::isOnBoard(Location location, Board *board)
{
   bool onBoard = false;
   if (location.row < board->getRows() && location.row >= 0)
   {
      if (location.col < board->getCols() && location.col >= 0)
      {
         onBoard = true;
      }
   }
   return onBoard;
}
