/* 
    nqueens.cpp

    author: Anthony Lupica <ar127@uakron.edu>
    purpose: solve the NQueens problem using the backtracking algorithm for some .csv input 
             representing a chessboard of size N x N. If a solution is found for N queens, 
             a .csv solution is produced. Otherwise, no solution is displayed.
    
    Information: This program was built and tested in an Ubuntu shell with CMake. 
                 It assumes the name of the input file is "input.csv" and is present in the build 
                 directory.
                 It also does not validate against the occurance of a non-square input,
                 or input that does not adhere to strictly comma-separated 0's and 1's.
                 It anticipates that 1 initial queen has been placed in some starting position as a given condition.

                 This implementation uses four std::unordered_sets to track row/column, positive diagonal, and negative 
                 diagonal information for each placed queen.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>        // isdigit() and isprint()
#include <unordered_set> // for sets of rows/columns, positive, and negative diagonals used 

using std::ifstream;
using std::cout;
using std::cin;
using std::vector;

void readFile(std::ifstream &inStream, int N); 
int findN();
void display();
int NQueens(int row);

// namepace containing sets for queen collisions
// each queen must occupy its own row/column, and positive/negative diagonal
namespace QueenPos
{
    std::unordered_set<int> rowSet;     // store row index
    std::unordered_set<int> colSet;     // store column index 
    std::unordered_set<int> posDiagSet; // Row + Col = constant for a given positive diagonal
    std::unordered_set<int> negDiagSet; // Row - Col = constant for a given negative diagonal
    
    // starting queen position (initQueen[0] = row && initQueen[1] = column)
    int initQueen[2];
}

// define a 2d vector (vector of vectors of chars)
vector<vector<char>> chessBoard;

int main()
{
    // declare and initialize in-file stream
    ifstream inStream("input.csv");

    // if file was successfully opened
    if (inStream)
    {
        // find what N is for the .csv input (assumes a square layout)
        int N = findN();
        
        // pass in the stream object and 2d vector by ref,
        // and the dimensions of the board
        readFile(inStream, N);

        // close the file stream
        inStream.close();

        // echo the chessboard structure to standard output
        cout << "\ninput file--> \n\n";
        display();

        // submit instatiated chessBoard to the backtracking recursive algorithm
        // if returned 1, output the solution board
        if (NQueens(0) == 1)
        {
            
            cout << "Solution found for a " << N << " by " << N << " chess board, with a given initial queen at (" 
                    << QueenPos::initQueen[0] << ", " << QueenPos::initQueen[1] << ")\n\n";
            
            display();
        }

        // otherwise, no solution could be found for the given N and/or the initial queen position provided 
        else 
        {
            cout << "No solution found for a " << N << " by " << N << " chess board, with a given initial queen at (" 
                 << QueenPos::initQueen[0] << ", " << QueenPos::initQueen[1] << ")\n\n";
        } 
    }

    else 
    {
        std::cerr << "\nFile could not be opened\n";
    }

    return 0;
}

/*  
    pre: assumes the existence of a file titled "input.csv" for input,
        and expects that it will be formatted in an N x N layout.
        It takes in an ifstream by reference and a vector of vectors of chars by reference.
        It also takes in N (returned by findN()), and uses it as the for-condition.
    post: Nested for-loops populate the vector from the stream. The inner-for fills the inner 
          vectors, which are then pushed to the outer vector. The global sets for column pos, 
          negative diagonal, and positive diagonal are updated for the initial queen position.
*/
void readFile(std::ifstream &inStream, int N)
{
    using namespace QueenPos;

    char getChar;
    
    // temp vector to store inner vectors 
    vector<char> temp;

    // fill the inner vectors, then use them to fill the outer vector 
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            // use loop to parse through commas
            do 
            {
                inStream.get(getChar);
            } while (getChar != '0' && getChar != '1');
            
            // intitial queen added to sets
            if (getChar == '1')
            {
                // store initial queen pos for later display
                initQueen[0] = i;
                initQueen[1] = j;
                
                // store row and col position
                rowSet.insert(i);
                colSet.insert(j);

                // store pos diag 
                posDiagSet.insert(i + j);

                // store neg diag
                negDiagSet.insert(i - j);
            }
            temp.push_back(getChar);
        }
        chessBoard.push_back(temp);
        
        // clear the temp vector 
        temp.clear();
    }

    return;
}

/* 
    pre: assumes the existence of a file titled "input.csv" for input,
        and expects that it will be formatted in an N x N layout.
        If the values are not arranged in a square, the file will 
        be truncated to the length of the first row.
    post: The dimensions of the file are returned.
*/
int findN()
{
    // declare and initialize temp file stream
    ifstream temp("input.csv");

    // char to hold input and N to hold width
    char getChar; 
    int N = 0;
    
    // loop reads number of 1's or 0's in first line to find N (assumes square)
    do
    {
        getChar = temp.get();

        // increment N if char is a digit (1 or 0)
        if (isdigit(getChar))
        {
            ++N;
        }
    } while (isprint(getChar)); // end if char is not printable

    temp.close();

    return N;
 }
 
 /* 
    pre: takes in the 2d vector containing the file input by reference.
    post: the 2d vector is output to the screen.
 */
 void display()
 {
    // chessBoard[i].size() checks the size of the vector rows
    for (int i = 0; i < chessBoard.size(); ++i)
    {
        for (int j = 0; j < chessBoard[i].size(); ++j)
        {
            cout << chessBoard[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    return;
 }

int NQueens(int row)
{
    using namespace QueenPos;

    // base case: if all queens have been placed, return true
    if (row == chessBoard.size())
    {
        return 1;
    }

    for (int col = 0; col < chessBoard[row].size(); ++col)
    {
        if ((colSet.count(col) == 0) && (negDiagSet.count(row - col) == 0) && (posDiagSet.count(row + col) == 0))
        {
            // ensure that this is not the initial (given) queen's row.
            // In the event that it were, we should not concern ourselves
            // with placing the queen. 
            if (row != initQueen[0])
            {
                // place a queen if it will not be attacked by another 
                // note: character '1' is 49 in dec
                chessBoard[row][col] = 49;

                rowSet.insert(row);
                colSet.insert(col);
                negDiagSet.insert(row - col);
                posDiagSet.insert(row + col);
            }
            
            // recursive call
            if (NQueens(row + 1))
            {
                return 1;
            }

            // if this path did not terminate in a solution, backtrack
            chessBoard[row][col] = 0;

            rowSet.erase(row);
            colSet.erase(col);
            negDiagSet.erase(row - col);
            posDiagSet.erase(row + col);
        }
    }

    // if this is reached, we exited leaving a row queen-less
    return 0;
}
