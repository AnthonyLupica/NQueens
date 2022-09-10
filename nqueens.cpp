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
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype> // isdigit() and isprint()

using std::ifstream;
using std::cout;
using std::cin;
using std::vector;

void readFile(std::ifstream &inStream, vector<vector<char>> &chessBoard, int N); 
int findN();
void display(const vector<vector<char>> &chessBoard);
int NQueens(int N);

int main()
{
    // declare and initialize in-file stream
    ifstream inStream("input.csv");

    // if file was successfully opened
    if (inStream)
    {
        // find what N is for the .csv input (assumes a square layout)
        int N = findN();
        
        // define a 2d vector (vector of vectors of chars)
        vector<vector<char>> chessBoard;

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

/*  
    pre: assumes the existence of a file titled "input.csv" for input,
        and expects that it will be formatted in an N x N layout.
        It takes in an ifstream by reference and a vector of vectors of chars by reference.
        It also takes in N (returned by findN()), and uses it as the for-condition.
    post: Nested for-loops populate the vector from the stream. The inner-for fills the inner 
          vectors, which are then pushed to the outer vector. The global sets for column pos, 
          negative diagonal, and positive diagonal are updated for the initial queen position.
*/
void readFile(std::ifstream &inStream, vector<vector<char>> &chessBoard, int N)
{
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
 void display(const vector<vector<char>> &chessBoard)
 {
    cout << "\ninput file--> \n\n";

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

int NQueens(int N)
{

}