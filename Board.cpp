#include "Board.h"
#include "TileCodes.h"

#define NO_OF_ROWS   26
#define NO_OF_COLS   26

Board::Board()
{
   theBoard.resize(NO_OF_ROWS, std::vector<Tile*>(NO_OF_COLS, nullptr));
   bag = new LinkedList();
}

Board::~Board()
{

}

LinkedList* Board::getBag()
{
   return bag;
}

bool Board::isSpotTaken(int Row, int Column)
{
   // std::cout << "row: "<<row<<" col: " << col <<std::endl; 
   bool check = false;
   if(theBoard[Column][Row] != nullptr)
   {
      check = true;
   }

   return check;
}

void Board::toString()
{
   std::string boardPrint = " ";


   // Should print 1 through 26
   for (int j= 0; j < 26; j++)
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

   for (int i= 0; i < 26*4; i++)
   {
      boardPrint.append("-");
   }
   boardPrint.append("\n");
   for (int i = 0; i != 26; i++)
   {
      char letter = i + 65;
      boardPrint += letter;
      boardPrint.append(" ");
      for (int j= 0; j < 26; j++)
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
   std::cout << boardPrint;
}

void Board::placeTile(Tile* newTile, int Row, int Column)
{
   theBoard[Column][Row] = newTile;
}