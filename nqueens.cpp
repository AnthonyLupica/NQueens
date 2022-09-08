/* 
    nqueens.cpp

    author: Anthony Lupica <ar127@uakron.edu>
    purpose: solve the NQueens problem using the backtracking algorithm for some .csv input 
             representing a chessboard of size N x N. If a solution is found for N queens, 
             a .csv solution is produced. Otherwise, no solution is displayed.
    
    Information: This program was built and tested in an Ubuntu shell. It will ask the user to specify the name
                 of the .csv (and path if necessary), as well as the dimensions of the board.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cctype> // isdigit() and isprint()

using std::ifstream;
using std::cout;
using std::cin;
using std::vector;

void readFile(std::ifstream &inStream, vector<vector<bool>> &chessBoard, int N); 
int findN();
void display(const vector<vector<bool>> &chessBoard);

int main()
{
    // declare and initialize in-file stream
    ifstream inStream("input.csv");

    // if file was successfully opened
    if (inStream)
    {
        // find what N is for the .csv input (assumes a square layout)
        int N = findN();
        
        // define a 2d vector (vector of vectors of bools)
        vector<vector<bool>> chessBoard;

        // pass in the stream object and 2d vector by ref,
        // and the dimensions of the board
        readFile(inStream, chessBoard, N);

        // close the file stream
        inStream.close();

        // echo the chessboard structure to standard output
        display(chessBoard);
    }

    else 
    {
        std::cerr << "\nFile could not be opened\n";
    }

    return 0;
}

void readFile(std::ifstream &inStream, vector<vector<bool>> &chessBoard, int N)
{
    bool getBool;

    // fill the inner vectors, then use them to fill the outer vector 
    for (int i = 0; i < N; ++i)
    {
        vector<bool> temp;
        for (int j = 0; j < N; ++j)
        {
            inStream >> getBool;
            temp.push_back(getBool);
        }
        chessBoard.push_back(temp);
    }

    return;
}

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
 
 void display(const vector<vector<bool>> &chessBoard)
 {
    // chessBoard[i].size() checks the size of the vector rows
    for (int i = 0; i < chessBoard.size(); ++i)
    {
        for (int j = 0; j < chessBoard[i].size(); ++j)
        {
            cout << chessBoard[i][j] << " ";
        }
        cout << std::endl;
    }

    return;
 }
