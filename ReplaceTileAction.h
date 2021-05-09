#include "Action.h"
#include "Tile.h"

class ReplaceTileAction : public Action{
public:

    ReplaceTileAction(Tile* replacedTile);
    ReplaceTileAction(std::string data);

    ~ReplaceTileAction();

    void doAction(Bag* bag, Board* board,Player* player);
    void undoAction(Bag* bag, Board* board,Player* player);

    std::string toString();

private:
    Tile* replacedTile;
    Tile* newTile;
};
