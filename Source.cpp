#include <iostream>
using namespace std;

#define N 9

class SudokuSolver
{
private:

    //check rows, cols and subgrid
    bool isSafe(int grid[N][N], int row, int col, int num)
    {
        for (int x = 0; x <= 8; x++)
            if (grid[row][x] == num)
                return false;

        for (int x = 0; x <= 8; x++)
            if (grid[x][col] == num)
                return false;

        int startRow = row - row % 3, startCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i + startRow][j + startCol] == num)
                    return false;

        //only safe if nothing was found
        return true;
    }

public:

    void print(int arr[N][N])
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << arr[i][j] << " ";
            cout << endl;
        }
    }

    bool solve(int grid[N][N], int row, int col)
    {
        //stop at end
        if (row == N - 1 && col == N)
            return true;

        if (col == N) {
            row++;
            col = 0;
        }

        // if cell already has value >0 go to next column
        if (grid[row][col] > 0)
            return solve(grid, row, col + 1);
        //check all possible numbers        
        for (int num = 1; num <= N; num++)
        {
            if (isSafe(grid, row, col, num))
            {
                //if safe to put, assume that answer is correct...
                grid[row][col] = num;
                if (solve(grid, row, col + 1))
                    return true;    //exit if successful
            }
            //if still here, revert and continue guessing
            grid[row][col] = 0;
        }
        return false;
    }
};

int main()
{
    // 0 means unassigned cells
    int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    SudokuSolver solver;
    if (solver.solve(grid, 0, 0))
        solver.print(grid);
    else
        cout << "no solution found" << endl;
    return 0;
}
