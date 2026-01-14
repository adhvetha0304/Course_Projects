/* ------------------------------------------------------------------------------
   Program: Outlast the Baddies & Avoid the Abyss
   Course: CS 211, Fall 2024
   Author: Adhvetha SP
   ------------------------------------------------------------------------------
   Description : A game where the Hero escapes through a grid while avoiding 
   obstacles and Baddies. Implements movement logic, collision handling, and 
   polymorphic board cells.
   ------------------------------------------------------------------------------
   */
#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

#include "boardcell.h"
#include "grid.h"

using namespace std;

class GameBoard {
	private: 
	    Grid<BoardCell*> board;
        size_t numRows;
        size_t numCols;
        size_t HeroRow; // Hero's position row
	    size_t HeroCol; // Hero's position column
        int numMonsters;
        int numSuperMonsters;
        int numAbysses;
        int numBats;
        bool wonGame; // false, unless the Hero reached the exit successfully

		
	public: 
		/* default constructor */
        GameBoard() {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 50;
            numBats = 2;
            wonGame = false;
            
            this -> numRows = 15;
            this -> numCols = 40;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* param constructor */
        GameBoard(size_t numRows, size_t numCols) {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 20;
            numBats = 3;
            wonGame = false;
            
            this -> numRows = numRows;
            this -> numCols = numCols;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* destructor */
        virtual ~GameBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    delete board(row, col);
                }
            }
        }
        /* Fills the board with empty cells */
        void blankBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    board(row, col) = new Nothing(row,col);
                }
            }
        }
        /* Returns the display character of a cell*/
        char getCellDisplay(size_t r, size_t c) {
            return board(r,c)->display();
        }
        /* Sets a specific cell to a given object */
        void setCell(BoardCell* myCell, size_t r, size_t c) {
            board(r,c) = myCell;
        }
        /* Frees the memory allocated to a specific cell*/
        void freeCell(size_t r, size_t c) {
            delete board(r,c);
        }

        /* Randomly places all the elements on the board*/
        void setupBoard(int seed) {
            srand(seed);
            size_t r,c;

            r = rand() % numRows;
            c = rand() % 3;
            delete board(r,c);
            board(r,c) = new Hero(r,c);
            HeroRow = r;
            HeroCol = c;

            r = rand() % numRows;
            c = numCols - 1 - (rand() % 3);
            delete board(r,c);
            board(r,c) = new EscapeLadder(r,c);
            
            int sizeMid = numCols - 6;

            c = 3 + (rand() % sizeMid);
            for (r = 0; r < numRows/2; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }
            size_t topc = c;

            while (c == topc || c == topc-1 || c == topc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows-1; r > numRows/2; --r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);           
            }
            size_t botc = c;

            while (c == topc || c == topc-1 || c == topc+1 || c == botc || c == botc-1 || c == botc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows/4; r < 3*numRows/4; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }

            for (int i = 0; i < numMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c);  
                board(r,c)->setPower(1);        
            }

            for (int i = 0; i < numSuperMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c); 
                board(r,c)->setPower(2);               
            }

            for (int i = 0; i < numBats; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Bat(r,c); 
            }

            for (int i = 0; i < numAbysses; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Abyss(r,c);              
            }
        }

        // neatly displaying the game board 
		void display( ) {
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            for (size_t row = 0; row < board.numrows(); row++) {
                cout << '|';
                for (size_t col = 0; col < board.numcols(row); col++) {
                    cout << board(row,col)->display();
                }
                cout << '|';
                cout << endl;
            }
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            
        }
		/* Returns the game status - true if the Hero has won */
        bool getWonGame() {
            return wonGame;
        }
       /* Sets the number of monsters and divides them into regular and super */
        void setNumMonsters(int num) {
            numSuperMonsters = num/3;
            numMonsters = num - numSuperMonsters;
        }
        /* Sets the number of Abyss cells*/
        void setNumAbysses(int num) {
            numAbysses = num;
        }
        /* Sets the number of Bats*/
        void setNumBats(int num) {
            numBats = num;
        }
        /* Returns the number of rows in the board*/
        size_t getNumRows() {
            return numRows;
        }
        /* Returns the number of columns in the board*/
        size_t getNumCols() {
            return numCols;
        }
  
        /* Gets the Hero's current position*/
        void getHeroPosition(size_t& row, size_t& col) {
            row = HeroRow;  
            col = HeroCol; 
        }

        /* Sets the Hero's current position*/
        void setHeroPosition(size_t row, size_t col) {
            HeroRow = row;
            HeroCol = col;
        }

        /* Updates the Hero's position by searching for it on the*/
        void findHero() {
            for(size_t row = 0; row < board.numrows(); row++){
                for(size_t col = 0; col < board.numcols(row); col++){
                    if(board(row, col) && board(row, col)->isHero()){
                        setHeroPosition(row,col);
                        return;
                    }
                }
            }
            setHeroPosition(-1, -1);
        }

        /* Executes one round of the game, handling Hero and Baddie movements*/
        bool makeMoves(char HeroNextMove) {
            // Reset movement flags for all board cells at the start of the round
            for(size_t row = 0; row < board.numrows(); row++){
                for(size_t col = 0; col < board.numcols(row); col++){
                    board(row,col)->setMoved(false);
                }
            }
            bool hRemoved = false; // Tracks if the Hero is removed from the board
            size_t HnewR = HeroRow, HnewC = HeroCol;
            try {
                board(HeroRow,HeroCol)->setNextMove(HeroNextMove);
                board(HeroRow,HeroCol)->attemptMoveTo(HnewR,HnewC,HeroRow,HeroCol);
               // Adjust position if Hero's move is out of bounds
                if (HnewR >= numRows) { 
                    HnewR = HeroRow;
                } 
                else if(HnewR < 0){
                    HnewR = HeroRow;
                }

                if (HnewC >= numCols) { 
                    HnewC = HeroCol;
                }
                else if(HnewC < 0){
                    HnewC = HeroCol;
                }

                // if(HnewR >= numRows || HnewC >= numCols || HnewR < 0 || HnewC < 0){
                //     throw out_of_range("Hero attempted to move out of bounds");
                // }


                if(board(HnewR, HnewC)->isBarrier()){
                    if(HnewR != HeroRow && HnewC != HeroCol){
                        HnewC = HeroCol;
                        if(board(HnewR, HnewC)->isBarrier()){
                            HnewR = HeroRow;
                        }
                    }
                    if(board(HnewR, HnewC)-> isBarrier()){
                        throw runtime_error("Hero attempted to move onto a barrier");
                    }
                }

                if(board(HnewR, HnewC)->isExit()){
                    cout << " Hero Escaped!"<<endl;
                    wonGame = true;
                    freeCell(HeroRow, HeroCol);
                    board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                    // setHeroPosition(-1,-1);
                    hRemoved = true;
                }


                if(board(HnewR, HnewC)->isHole()){
                    cout << "Hero fell into the Abyss!"<< endl;
                    freeCell(HeroRow, HeroCol);
                    board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                    // setHeroPosition(-1,-1);
                    hRemoved = true;
                }
                if(board(HnewR, HnewC)->isBaddie()){
                    cout << "Hero was captured by a Baddie!" << endl;
                    freeCell(HeroRow, HeroCol);
                    board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                    // setHeroPosition(-1,-1);
                    hRemoved = true;
                }
                if(board(HnewR,HnewC)->isSpace()){
                    freeCell(HnewR, HnewC);
                    board(HnewR, HnewC) = board(HeroRow, HeroCol);
                    board(HnewR, HnewC)->setRow(HnewR);
                    board(HnewR, HnewC)->setCol(HnewC);
                    board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                    setHeroPosition(HnewR, HnewC);
                }
            }
            catch (const runtime_error& excpt) {
                cout << excpt.what() << endl;
                cout << "Hero stays in place due to an invalid move." << endl;
            }
            
            //Loop through all the Baddies and execute their moves
            for(size_t row = board.numrows(); row-- > 0;){
                for(size_t col = board.numcols(row); col-- > 0;){
                    if(!board(row,col)->isBaddie()|| board(row,col)->getMoved()){
                        continue;
                    }

                    BoardCell* baddie = board(row,col);
                    // baddie->setMoved(true);

                    size_t BnewR = row, BnewC = col;
                    if(HeroRow != (size_t)-1 && HeroCol != (size_t)-1){
                        baddie->attemptMoveTo(BnewR, BnewC, HeroRow, HeroCol);
                    }
                    else{
                        BnewR = row;
                        BnewC = col;
                    }

                    if(BnewR >= numRows){
                        BnewR = row;
                    }
                    if(BnewC >= numCols){
                        BnewC = col;
                    }

                    if(board(BnewR, BnewC)->isBarrier() || board(BnewR, BnewC)->isExit()){
                            
                        if(BnewR != row && BnewC !=col){
                            BnewC = col;
                    
                            if(board(BnewR, BnewC)->isBarrier() || board(BnewR, BnewC)->isExit()){
                                BnewR = row;
                                  
                                if(board(BnewR, BnewC)->isBarrier() || board(BnewR, BnewC)->isExit()){
                                    BnewR = row;
                                    BnewC = col;
                            }
                        } 
                    }
                    else{
                        BnewR = row;
                        BnewC = col;
                    }
                }
            if(board(BnewR, BnewC)->isHole()){
                cout << "Baddie fell into the Abyss!" << endl;
                baddie->setMoved(true);
                freeCell(row,col);
                board(row, col) = new Nothing(row, col);
                continue;
            }

            if(board(BnewR, BnewC)->isBaddie()){
                baddie->setMoved(true);
                continue;
            }

            if(board(BnewR, BnewC)->isHero()){
                cout << "Hero was captured by a Baddie!" << endl;
                freeCell(BnewR, BnewC);
                board(BnewR, BnewC) = baddie;
                baddie->setRow(BnewR);
                baddie->setCol(BnewC);
                board(row,col) = new Nothing(row,col);
                baddie->setMoved(true);
                // setHeroPosition(-1,-1);
                hRemoved = true;
                continue;
            }

            if(board(BnewR, BnewC)->isSpace()){
                freeCell(BnewR, BnewC);
                board(BnewR, BnewC) = baddie;
                baddie->setRow(BnewR);
                baddie->setCol(BnewC);
                board(row,col) = new Nothing(row,col);
                baddie->setMoved(true);
                continue;
             }

            baddie->setMoved(true); //marks baddie as moved
                }
            }
            // Update Hero's position or mark as removed
            if(hRemoved){
                setHeroPosition(-1,-1);
            }
            else{
                 findHero();
            }
            return ((HeroRow != (size_t)-1 && HeroCol != (size_t)-1));
    }
};
#endif //_GAMEBOARD_H  