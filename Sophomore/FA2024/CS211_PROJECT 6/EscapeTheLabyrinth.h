#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

const string kYourNetID = "asath7";

const string kPathOutOfRegularMaze = "ESSESENSWNNNES";
const string kPathOutOfTwistyMaze = "SEENESSN";

bool isPathToFreedom(MazeCell *start, const string& moves) {
    if(!start){
        return false;
    }
    bool spellbook = false, potion = false, wand = false;
    MazeCell* cell = start;

    if(cell->whatsHere == "Spellbook") spellbook = true;
    else if(cell->whatsHere == "Potion") potion = true;
    else if(cell->whatsHere == "Wand") wand = true;

    for(char move: moves){
        MazeCell* nextCell = nullptr;
        switch(move){
            case 'N':
               nextCell = cell->north;
               break;
            case 'S':
               nextCell = cell->south;
               break;
            case 'E':
               nextCell = cell->east;
               break;
            case 'W':
               nextCell = cell->west;
               break;
            default:
                return false;
        }
        if(nextCell){
            cell = nextCell;
            
            if(cell->whatsHere == "Spellbook") spellbook = true;
            else if(cell->whatsHere == "Potion") potion = true;
            else if(cell->whatsHere == "Wand") wand = true;
        }
        else{
            return false;
        }
    } 
    return spellbook && potion && wand;
}
