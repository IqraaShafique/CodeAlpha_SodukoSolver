#include <iostream>
#include <vector>

using namespace std;

const int N = 9; // Size of Sudoku grid

// Function to set the console text color using ANSI escape
void SetColor(int textColor)
{
    cout << "\033[" << textColor << "m";
}
struct SodukoSolver {
    //vector<vector<int>> grid(N, vector<int>(N, 0));

    vector<vector<int>> getInput(vector<vector<int>> gr)
    {
        SetColor(35);
        cout << "--------------------------------------------------------------------------------------------------\n";
        cout << "                                  SODUKO PUZZLE SOLVER\n";
        cout << "--------------------------------------------------------------------------------------------------\n\n";

        SetColor(34);
        cout << "Enter Sudoku puzzle (9x9 grid, use 0 for empty cells):\n\n";
        for (int row = 0; row < N; ++row) 
        {
            for (int col = 0; col < N; ++col) 
            {
                SetColor(36);
                cout << "Enter value for cell (" << row + 1 << ", " << col + 1 << "): ";
                SetColor(32);
                cin >> gr[row][col];
            }
        }
        cout << endl;
        return gr;
    }
    //function to print the unsolved Sudoku grid
    void printGrid(vector<vector<int>>& grid)
    {
        for (int row = 0; row < N; ++row)
        {
            for (int col = 0; col < N; ++col)
            {
                cout << grid[row][col] << " ";
                if ((col + 1) % 3 == 0 && col != N - 1)
                    cout << "| ";
            }
            cout << endl;
            if ((row + 1) % 3 == 0 && row != N - 1)
            {
                cout << "------+-------+------" << endl;
            }
        }
    }

    //function to check if a number can be placed in a specific position (row, col)
    bool isSafe(vector<vector<int>>& grid, int row, int col, int num)
    {
        //Check if the number is already present in the current row or column
        for (int x = 0; x < N; ++x)
        {
            if (grid[row][x] == num || grid[x][col] == num)
                return false;
        }

        // Check in the current 3x3 grid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (grid[startRow + i][startCol + j] == num)
                    return false;
            }
        }

        return true;
    }

    // Function to solve Sudoku using backtracking
    bool solveSudoku(vector<vector<int>>& grid)
    {
        int row, col;

        // Find an empty cell
        bool foundEmpty = false;
        for (row = 0; row < N; ++row)
        {
            for (col = 0; col < N; ++col)
            {
                if (grid[row][col] == 0)
                {
                    foundEmpty = true;
                    break;
                }
            }
            if (foundEmpty)
                break;
        }

        // If no empty cell found, puzzle is solved
        if (!foundEmpty)
            return true;

        // Try placing numbers from 1 to 9
        for (int num = 1; num <= 9; ++num)
        {
            if (isSafe(grid, row, col, num))
            {
                grid[row][col] = num;

                // Recursively solve the rest of the puzzle
                if (solveSudoku(grid))
                    return true;

                // Backtrack
                grid[row][col] = 0;
            }
        }

        // If no number can be placed, backtrack
        return false;
    }
};
int main() 
{
    SodukoSolver s;

    vector<vector<int>> grid(N, vector<int>(N, 0));

    //getting input from user
    grid=s.getInput(grid);

    //priting the soduko given by user
    SetColor(94);
    cout << "Sudoku puzzle to solve:\n\n";
    SetColor(32);
    s.printGrid(grid);
    cout << endl;

    if (s.solveSudoku(grid)) 
    {
        //in case soduko is solvable print the solved puzzle
        SetColor(94);
        cout << "Solution:\n\n";

        SetColor(33);
        s.printGrid(grid);
        cout << endl;
    }
    else 
    {
        //else print it is not solvable
        SetColor(31);
        cout << "No solution exists." << endl;
    }

    SetColor(37);
    return 0;
}
