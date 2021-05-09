#include "PlaceTileAction.h"
#include <sstream>

PlaceTileAction::PlaceTileAction(Tile* playedTile, std::string boardLocation, int score):Action(){
    this->playedTile = playedTile;
    this->boardLocation = boardLocation;
    this->score = score;
    newTile = nullptr;
}

PlaceTileAction::PlaceTileAction(std::string data){
    std::istringstream delimitedData (data);
   
    std::string playedTileData,boardLocationData,newTileData;

    std::getline(delimitedData,playedTileData,',');
    std::getline(delimitedData,boardLocationData,',');
    std::getline(delimitedData,newTileData,',');

    playedTile = new Tile(playedTileData);
    boardLocation = boardLocationData;
    newTile = new Tile(newTileData); 
}

PlaceTileAction::~PlaceTileAction(){
    if(newTile != nullptr)
        delete newTile;
}

//***No validation*** expects a correct and legal move
void PlaceTileAction::doAction(Bag* bag, Board* board,Player* player){
    //removing tile from players hand and moving it to the board
    player->removeTile(playedTile);
    board->placeTile(playedTile,boardLocation);

    //Updating player score
    player->addScore(score);

    //Getting new tile from bag and adding to players hand
    newTile = bag->getFront();
    player->addTile(new Tile(*newTile));
}

//***No validation*** excpects bag,player,board to be in the state left by doAction 
void PlaceTileAction::undoAction(Bag* bag, Board* board,Player* player){
    //Remove new tile from players hand and replacing it in bag
    player->removeTile(newTile);
    bag->replaceFront(new Tile(*newTile));

    //removing score
    player->addScore(-score);

    //Removing tile from board and replacing into players hand
    board->removeTile(boardLocation);
    player->addTile(playedTile);
}

std::string PlaceTileAction::toString(){
    std::string build = "PlaceTile\n";
    build.append(playedTile->getTileName() + ",");
    build.append(boardLocation + ",");
    build.append(newTile->getTileName() + ",");
    build.append(std::to_string(score));

    return build;
}