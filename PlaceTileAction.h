#include "Action.h"
#include "Tile.h"

class PlaceTileAction : public Action{
public:

    PlaceTileAction(Tile* playedTile, std::string boardLocation, int score);
    PlaceTileAction(std::string data);

    ~PlaceTileAction();

    void doAction(Bag* bag, Board* board,Player* player);
    void undoAction(Bag* bag, Board* board,Player* player);

    std::string toString();

private:
    Tile* playedTile;
    Tile* newTile;
    int score;
    std::string boardLocation;
};