#include "Controller.h"
#include <regex>
#define PLAYER_ONE  1
#define PLAYER_TWO  2

Controller::Controller(Player* playerOne, Player* playerTwo, Bag* bag){
    this->playerOne = playerOne;
    this->playerTwo = playerTwo;
    this->bag = bag;
    board = new Board();
    gameHistory = new GameHistory(bag, playerOne, playerTwo);
}


Controller::Controller(Player* one, Player* two, Bag* bag,Board* board, GameHistory* history){
    playerOne = one;
    playerTwo = two;
    this->bag = bag;
    this->board = board;
    gameHistory = history;
}

Controller::~Controller(){
    delete playerOne;
    delete playerTwo;
    delete bag;
    delete board;
    delete gameHistory;
}

void Controller::gameplay(int playersNextTurn) {

    int playersTurn = playersNextTurn;
    bool lastTurnLeft = false, gameOver = false, quitGame = false;

    do { //while 'quit' is not selected
        bool endTurn = false;
        if (bagEmpty()) {
            if (!lastTurnLeft) {
                std::cout << "The bag is empty! This will be your last turn" << std::endl;
                lastTurnLeft = true;
            }
            else {
                gameOver = true;
            }
        }

        do { //while still player's turn
            if (playersTurn == PLAYER_ONE) {
                std::cout << playerOne->getName() << ", it's your turn" << std::endl;
                displayScoreAndBoard();
                std::cout << "Your hand is\n" << playerOne->playerHand() << std::endl;
            } else {
                std::cout << playerTwo->getName() << ", it's your turn" << std::endl;
                displayScoreAndBoard();
                std::cout << "Your hand is\n" << playerTwo->playerHand() << std::endl;
            }

            std::cout << "What would you like to do?" << std::endl;
            std::string input; //For user input
            bool validInput = false; //Ensures user won't exit the loop until a valid input is registered
            std::smatch match;
            std::regex placeInputValid("place [ROYGBP][1-6] at [A-Z](\\d\\d|\\d)");
            std::regex replaceInputValid("replace [ROYGBP][1-6]");
            std::regex saveFileNameValid("\\w{1,}");
            do { //while input is not valid
                std::cout << ">";
                std::cin >> std::ws;
                getline(std::cin, input);
                //Place Tile
                if (std::regex_match(input, match, placeInputValid)) {
                    std::string tileName = input.substr(6, 2);
                    std::string boardLocation = input.substr(12, 3);
                    Tile *requestedTile = new Tile(tileName);
                    if (tileInHand(playersTurn, tileName)) {
                        if (validPlaceTile(requestedTile, boardLocation, board->boardEmpty())) {
                            validInput = true;
                            placeTile(playersTurn, requestedTile, boardLocation,
                                      calcScore(requestedTile, boardLocation));
                            endTurn = true;
                        }
                    }
                    //Replace Tile
                } else if (std::regex_match(input, match, replaceInputValid)) {
                    std::string tileName = input.substr(8, 2);
                    std::cout << "User wants to replace " << tileName << "." << std::endl;
                    Tile *requestedTile = new Tile(tileName);
                    if (tileInHand(playersTurn, tileName)) {
                        if (validReplaceTile(requestedTile, playersTurn)) {
                            validInput = true;
                            replaceTile(playersTurn, requestedTile);
                            endTurn = true;
                        }
                    }
                    //Undo
                } else if (input.find("undo") == 0) {
                    //ToDo move p1 & p2 undo count to GameHistory
                    if (playersTurn == PLAYER_ONE && gameHistory->getPlayerOneUndos() != 0) {
                        gameHistory->undo(bag, board, playerOne, playerTwo);
                        gameHistory->setPlayerOneUndos(gameHistory->getPlayerOneUndos() - 1);
                        std::cout << playerOne->getName() << ", you have "
                                  << gameHistory->getPlayerOneUndos() << " undo actions left." << std::endl;
                    } else if (playersTurn == PLAYER_TWO && gameHistory->getPlayerTwoUndos() != 0) {
                        gameHistory->undo(bag, board, playerOne, playerTwo);
                        gameHistory->setPlayerTwoUndos(gameHistory->getPlayerTwoUndos() - 1);
                        std::cout << playerTwo->getName() << ", you have "
                                  << gameHistory->getPlayerTwoUndos() << " undo actions left." << std::endl;
                    } else {
                        std::cout << "You have ran out of Undo actions!" << std::endl;
                    }
                    validInput = true;
                    //Save Game
                } else if (input.find("save") == 0) {
                    std::string saveFileName;
                    std::cout << "Input a name for your save file" << std::endl;
                    std::cout << ">";
                    std::cin >> saveFileName;
                    save(saveFileName + ".save",playersTurn);
                    validInput = true;
                    //Quit Game
                } else if (input.find("quit") == 0) {
                    std::cout << "exiting game..." << std::endl;
                    validInput = true;
                    endTurn = true;
                    quitGame = true;
                }
                if (!validInput) {
                    std::cout << "Improper input, please use 'place', 'replace', 'undo', 'save', or 'quit'."
                              << std::endl;
                    input.clear();
                }
            } while (!validInput);
        }
        while (!endTurn);
        //Turn is over
        playersTurn == PLAYER_ONE ? playersTurn = PLAYER_TWO : playersTurn = PLAYER_ONE; //Alternates player turns.
        if (gameOver) {
            std::string winnerName;
            int winnerScore;
            if (playerOne->getScore() > playerTwo->getScore()){
                winnerName = playerOne->getName();
                winnerScore = playerOne->getScore();
            }
            else if (playerTwo->getScore() > playerOne->getScore()){
                winnerName = playerTwo->getName();
                winnerScore = playerTwo->getScore();
            }
            else {
                winnerName = "... It's tie! You both";
                winnerScore = playerOne->getScore();
            }
            std::cout << "Congratulations " << winnerName << " won with a score of: " << winnerScore << std::endl;
            std::cout << "Would you like to see a 'replay' of this match, or would you like to 'quit'?" << std::endl;
            std::string input; //For user input
            bool validEndInput = false; //Ensures user won't exit the loop until a valid input is registered
            do { //while input is valid
                std::cout << ">";
                std::cin >> std::ws;
                getline(std::cin, input);
                if (input.find("replay") == 0) {
                    gameHistory->replay();
                    validEndInput = true;
                    quitGame = true;
                }
                else if (input.find("quit") == 0){
                    validEndInput = true;
                    quitGame = true;
                }
            } while (!validEndInput);
        }
    } while (!quitGame);
};

void Controller::displayScoreAndBoard(){
    std::cout << "Score for " << playerOne->getName() << ": " << playerOne->getScore() << std::endl
    << "Score for " << playerTwo->getName() << ": " << playerTwo->getScore() << std::endl
    << board->toString() << std::endl;
};

//Checks amount of tiles left in bag. Once no tiles are left each player is allowed one turn
bool Controller::bagEmpty(){
    bool isBagEmpty = false;
    if (bag->getBag()->getSize() == 0){
        isBagEmpty = true;
    }
    return isBagEmpty;
}

//Saves the game! 💾
void Controller::save(std::string filename, int playersTurn){
    std::ofstream saveFile;

    saveFile.open(filename);
    //saving players,bag and board
    saveFile << playerOne->toString() << std::endl;
    saveFile << playerTwo->toString() << std::endl;
    saveFile << board->toString() << std::endl;
    saveFile << bag->toString() << std::endl;
    //Saving whos turn it is next
    if(playersTurn == PLAYER_ONE)
        saveFile << playerOne->getName() << std::endl;
    else
        saveFile << playerTwo->getName() << std::endl;

    //saving game history
    saveFile << gameHistory->toString() << std::endl;

    saveFile.close();
}

bool Controller::tileInHand(PlayerNum playerNum, std::string tileName){
    bool foundTile = false;
    if (playerNum == PLAYER_ONE) { //Checks against Player One's hand
        if (playerOne->getHand()->searchTile(tileName) != -1) {
            foundTile = true;
        }
        else{
            std::cout << "That tile is not in your hand!" << std::endl;
        }
    } else { //Checks against Player Two's hand
        if (playerTwo->getHand()->searchTile(tileName) != -1) {
            foundTile = true;
        }
        else {
            std::cout << "That tile is not in your hand!" << std::endl;
        }
    }
    return foundTile;
}

bool Controller::validPlaceTile(Tile* playedTile, std::string boardLocation, bool firstTile){
    int row, column;
    bool result = false;

    column = boardLocation[0]-65; // gets from A,B,C,...

    //Converting Strings to Integers
    row = stoi(boardLocation.substr(1));  //shows 1,2,3,...

    //checks if the tile that we are placing is inside of bounds, otherwise return false
    if(row >= MAX_SIZE || column >= MAX_SIZE )
        std::cout << "There are no more than 25 rows and columns, therefore you cannot add the tile in this position";
    else if(row % 2 != column % 2)
        std::cout << "\n You can't place a tile there" << std::endl;
    else if(board->board[column][row].compare(EMPTY_TILE) != 0)
        std::cout << "\n There is a tile already in that position" << std::endl;
    else if(firstTile){
        result = true;
    }
    else{
        int newRow, newCol;

        bool badNeighbour = false;
        bool goodNeighbour = false;

        //checks the surroundings of the tile
        for(int dir = 1; dir <= 4 && !badNeighbour; dir++){
            newRow = row;
            newCol = column;

            if(dir == DOWNRIGHT){
                newCol++;
                newRow++;
            }
            else if(dir == DOWNLEFT){
                newCol++;
                newRow--;
            }
            else if(dir == UPRIGHT){
                newCol--;
                newRow++;
            }
            else if(dir == UPLEFT){
                newCol--;
                newRow--;
            }

            //only checks adjacent tiles in bounds of board
            if(newRow >= 0 && newRow < MAX_SIZE && newCol >= 0 && newCol < MAX_SIZE){
                //looks at all 4 sides to see if the position is empty. 
                if(board->board[newCol][newRow].compare(EMPTY_TILE) != 0){
                    if(board->board[newCol][newRow].compare(playedTile->getTileName()) != 0){
                        //This is to check if the tile has the same colour as the tile that's already in the board
                        if(playedTile->getTileName()[0] == board->board[newCol][newRow][0]){
                            int offsetRow = newRow - row;
                            int offsetCol = newCol - column;

                            newRow+=offsetRow;
                            newCol+=offsetCol;
                            //Goes through line of tiles insuring they all share the same colour
                            while(newRow >= 0 && newRow < MAX_SIZE && 
                                        newCol >= 0 && newCol < MAX_SIZE &&
                                        board->board[newCol][newRow].compare(EMPTY_TILE) != 0 &&
                                        !badNeighbour){

                                //Checking if the same tile is already in the line
                                if(playedTile->getTileName().compare(board->board[newCol][newRow]) == 0){
                                    std::cout << "\n You can not place the same tile twice in a line." << std::endl;
                                    badNeighbour = true;
                                }
                                else if(playedTile->getTileName()[0] != board->board[newCol][newRow][0]){
                                    badNeighbour = true;
                                    std::cout << "\n Each diagonal must share a common shape or colour." << std::endl;
                                }

                                newRow += offsetRow;
                                newCol += offsetCol;
                            }
                            goodNeighbour = true;
                        }

                        //This is to check if the tile has the same shape as the tile that's already in the board
                        else if(playedTile->getTileName()[1] == board->board[newCol][newRow][1]){
                            int offsetRow = newRow - row;
                            int offsetCol = newCol - column;

                            newRow += offsetRow;
                            newCol += offsetCol;
                            
                            //Goes through line of tiles insuring they all share the same shape
                            while(newRow >= 0 && newRow < MAX_SIZE && 
                                        newCol >= 0 && newCol < MAX_SIZE &&
                                        board->board[newCol][newRow].compare(EMPTY_TILE) != 0 &&
                                        !badNeighbour){
                                //Checking if the same tile is already in the line
                                if(playedTile->getTileName().compare(board->board[newCol][newRow]) == 0){
                                    std::cout << "\n You can not place the same tile twice in a line." << std::endl;
                                    badNeighbour = true;
                                }
                                else if(playedTile->getTileName()[1] != board->board[newCol][newRow][1]){
                                    badNeighbour = true;
                                    std::cout << "\n Each diagonal must share a common shape or colour." << std::endl;
                                }
                                newRow += offsetRow;
                                newCol += offsetCol;
                            }
                            goodNeighbour = true;
                        }
                        else{
                            std::cout << "\n You can only place a tile if it has the same colour or shape as adjacent tiles." << std::endl;
                            badNeighbour = true;
                        }
                    }
                    else{
                        std::cout << "\n You can not place the same tile twice in a line." << std::endl;
                        badNeighbour = true;
                    }
                }
            }
        }
        //if all four tile's neighbour is empty, then place the tile.
        if(!badNeighbour){
            if(goodNeighbour)
                result = true;
            else
                std::cout << "\n You can only place a tile if it is adjacent to at least one other tile." << std::endl;
        }
    }
    return result;
}

int Controller::calcScore(Tile* playedTile, std::string boardLocation){
    int returnScore = 0;

    int row, col;
    col = boardLocation[0]-65; // gets from A,B,C,...
    //Converting Strings to Integers
    row = stoi(boardLocation.substr(1));

    //number of tiles in \ diagonal
    int numTilesBackDiagonal = 0;
    //number of tiles in / diagonal
    int numTilesForwardDiagonal = 0;

    int offsetRow, offsetCol;
    for(int dir = 1; dir <= 4; dir++){

        if(dir == DOWNRIGHT){
            offsetCol = 1;
            offsetRow = 1;
        }
        else if(dir == UPRIGHT){
            offsetCol = 1;
            offsetRow = -1;
        }
        else if(dir == DOWNLEFT){
            offsetCol = -1;
            offsetRow = 1;
        }
        else {
            offsetCol = -1;
            offsetRow = -1;
        }

        int newRow = row + offsetRow;
        int newCol = col + offsetCol;

        while(newRow >= 0 && newRow < MAX_SIZE && 
                    newCol >= 0 && newCol < MAX_SIZE &&
                    board->board[newCol][newRow].compare(EMPTY_TILE) != 0){
            returnScore++;
            if(dir == UPLEFT || dir == DOWNRIGHT)
                numTilesBackDiagonal++;
            else 
                numTilesForwardDiagonal++;
            
            newRow += offsetRow;
            newCol += offsetCol;
        } 
    }

    //Adding extra point for the tile currently being placed
    if(numTilesForwardDiagonal>0)
        returnScore++;
    if(numTilesBackDiagonal>0)
        returnScore++;
    
    //Adding bonus 6 points if a qwirkle is score in either direction
    if(numTilesForwardDiagonal == 5){
        returnScore += 6;
        std::cout << "Qwirkle!" << std::endl;
    }
    if(numTilesBackDiagonal == 5){
        returnScore += 6;
        std::cout << "Qwirkle!" << std::endl;
    }
    return returnScore;
}

bool Controller::validReplaceTile(Tile* replacedTile, int playerNum){
    bool result = false;
    int position;

    //searches the position of the tile in player's hand
    if(playerNum == PLAYER_ONE)
        position = playerOne->getHand()->searchTile(replacedTile->getTileName());
    else 
        position = playerTwo->getHand()->searchTile(replacedTile->getTileName());

    //checks to see if that tile exist in player's hand
    if(position != -1)
        result = true;
    else
        std::cout << "The tile you want to replace doesn't exist in your hand." << std::endl;

    return result;
}

//Updates bag, board, players with new move and add move to history
//Validation to be implemented before calling this method
void Controller::placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation,int score){
    Action* newAction = new PlaceTileAction(playedTile, boardLocation,score);
    if(playerNum == PLAYER_ONE)
        newAction->doAction(bag,board,playerOne);
    else
        newAction->doAction(bag,board,playerTwo);
    
    gameHistory->addAction(newAction,playerNum);
}

//Updates bag, board, players with new move and add move to history
//Validation to be implemented before calling this method
void Controller::replaceTile(PlayerNum playerNum, Tile* replacedTile){
    Action* newAction = new ReplaceTileAction(replacedTile);
     if(playerNum == PLAYER_ONE)
        newAction->doAction(bag,board,playerOne);
    else
        newAction->doAction(bag,board,playerTwo);
    gameHistory->addAction(newAction, playerNum);
}
