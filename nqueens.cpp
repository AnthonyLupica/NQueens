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

using std::ifstream;
using std::cout;
using std::cin;
using std::vector;

void readFile(std::ifstream &inStream, vector<vector<bool>> &chessBoard, int N); 
int findN(std::ifstream &inStream);
void display(const vector<vector<bool>> &chessBoard);

int main()
{
    // in-file pointer
    std::ifstream inStream;

    // prompt for the file name
    char fileName[16];
    cout << "Enter the file name for input into NQueens (maximum of 15 characters): ";
  
    // flag for loops
    bool isValid;

    // validate fileName 
    do 
    {
        isValid = true;
        
        cin >> fileName;
        if (strlen(fileName) > 15)
        {
            cout << "invalid entry: ";
            isValid = false;

            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (!isValid);

    // prompt for dimensions
    int N = 0;
    cout << "Enter the dimensions (N) for the chessBoard (assumes square layout): ";

    // validate dimensions
    do 
    {
        isValid = true;
        
        cin >> N;
        if (cin.fail() || N < 0)
        {
            cout << "invalid entry: ";
            isValid = false;
            
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (!isValid);
  
    // open the user's file 
    inStream.open(fileName);

    // if file was successfully opened
    if (inStream)
    {
        // find what N is for the .csv input (assumes a square layout)
        //int N = findN(inStream);
        
        // define a 2d vector (vector of vectors of bools)
        vector<vector<bool>> chessBoard;

        // pass in the stream object and 2d vector by ref,
        // and the dimensions of the board
        readFile(inStream, chessBoard, N);

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

    // close the file stream
    inStream.close();

    return;
}

/*
int findN(std::ifstream &inStream)
{
    char temp; 
    int N = 0;

    while (N != '\n')
    {
        inStream.get(temp);
        ++N;
    }

    return N;
 }
 */

 void display(const vector<vector<bool>> &chessBoard)
 {
    // chessBoard[i].size() checks the size of the vector rows
    for (int i = 0; i < chessBoard.size(); ++i)
    {
        for (int j = 0; j < chessBoard[i].size(); ++j)
        {
            cout << chessBoard[i][j];
        }
        cout << std::endl;
    }

    return;
 }
