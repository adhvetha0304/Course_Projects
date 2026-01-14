/* ------------------------------------------------------------------------------
   Program: Escape the Labyrinth - Find Path to Freedom
   Course: CS 211, Fall 2024
   Author: Adhvetha SP
   ------------------------------------------------------------------------------
   Description : This program finds a valid escape path from a personalized 
   labyrinth while collecting the Spellbook, Potion, and Wand. It uses gdb to 
   systematically explore and map the maze.
   
   ------------------------------------------------------------------------------
   */

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
  struct ROW {
    T*  Cols;     // array of column elements
    size_t NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // array of ROWs
  size_t  NumRows;  // total # of rows (0..NumRows-1)
    
public:

/* Called automatically by to construct a 4x4 Grid. 
    All elements initialized to default value of T.*/

  Grid() {
    Rows = new ROW[4];  // 4 rows
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (size_t r = 0; r < NumRows; ++r) {
      Rows[r].Cols = new T[4];
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (size_t c = 0; c < Rows[r].NumCols; ++c) {
        Rows[r].Cols[c] = T();  // default value for type T:
      }
    }
  }
  
/* Called automatically to construct a Grid 
     with R rows, where each row has C columns. 
     All elements initialized to default value of T.*/

  Grid(size_t R, size_t C) {
    if(R == 0 || C == 0){
        R = 4;
        C = 4;
    }
    NumRows = R;
    Rows = new ROW[NumRows];
    for(size_t r = 0; r < NumRows; r++){
        Rows[r].Cols = new T[C];
        Rows[r].NumCols = C;
        for(size_t c = 0; c < Rows[r].NumCols; c++){
            Rows[r].Cols[c] = T();
        }
    }
  }
    

//Called automatically to free memory for this Grid.
  virtual ~Grid() {
    for(size_t r = 0; r < NumRows; r++){
        delete[] Rows[r].Cols;
    }
    delete[] Rows;
  }

/*Called automatically to construct a Grid that contains a
    copy of an existing Grid.  Example: this occurs when passing
    Grid as a parameter by value */
  Grid(const Grid<T>& other) {
    NumRows = other.NumRows;
    Rows = new ROW[NumRows];
    for(size_t r = 0; r < NumRows; r++){
        Rows[r].NumCols = other.Rows[r].NumCols;
        Rows[r].Cols = new T[Rows[r].NumCols];
        for(size_t c = 0; c < Rows[r].NumCols;c++){
            Rows[r].Cols[c] = other.Rows[r].Cols[c];
        }
    }
  }
    

// Called when one Grid is assigned into another, i.e. this = other;
  Grid& operator=(const Grid& other) {
    if(this != &other){
        Grid<T> temp(other);

        ROW* tempRows = Rows;
        Rows = temp.Rows;
        temp.Rows = tempRows;

        size_t tempNumRows = NumRows;
        NumRows = temp.NumRows;
        temp.NumRows = tempNumRows;
    }

    return *this;  
  }

// Returns the # of rows in the Grid.  
  size_t numrows() const {    
    return NumRows;  
  }
  
// Returns the # of columns in row r.    
  size_t numcols(size_t r) const {
    return (r < NumRows) ? Rows[r].NumCols : 0;
  }

// Returns the total # of elements in the Grid.
  size_t size() const {
    size_t total = 0;
    for(size_t r = 0; r < NumRows; r++){
        total += Rows[r].NumCols;
    }
      return total; 
  }

 /*Returns a reference to the element at location (r, c);
   this allows you to access or assign the element*/

  T& operator()(size_t r, size_t c) {
      static T temp = T();
      if(!(r < NumRows && c < Rows[r].NumCols)){
        throw std::out_of_range("Out of range");
        // std::cerr << "Out of Bounds!\n";
        // return temp;
      }
      return Rows[r].Cols[c];
  }

// Outputs the contents of the grid; for debugging purposes.  
  void _output() {
    for(size_t r = 0; r < NumRows; r++){
        for(size_t c = 0; c < Rows[r].NumCols; c++){
            cout << Rows[r].Cols[c] << " ";
        }
        cout << endl;
    }
  }

};
