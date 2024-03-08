#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
using namespace std;




// maximum number of rotations
int best = 13;

// number of rows, columns and total moves
int r,c,m;

// vector of 2D arrays, storing previous states of the grid.
vector<int**> patterns;



int** shallowCopy(int **original) {
    int** copy = new int*[r];

    for (int i = 0; i < r; ++i) {
        copy[i] = new int[c];
        for (int j = 0; j < c; ++j) {
            copy[i][j] = original[i][j];
        }
    }
    return copy;
}

void clear_grid(int **grid)
{
    for(int j = 0; j < r; j++)
    {
        delete[] grid[j];
    }
    delete[] grid;
}

int** rotate_left(int **grid,int x,int y)
{
    //(0,1)
    int** copiedArray = shallowCopy(grid);
    int temp = grid[0+x][0+y];
    copiedArray[0+x][0+y] = grid[0+x][1+y];
    copiedArray[0+x][1+y] = grid[1+x][1+y];
    copiedArray[1+x][1+y] = grid[1+x][0+y];
    copiedArray[1+x][0+y] = temp;
    return copiedArray;
}

int** rotate_right(int **grid,int x,int y)
{
    int** copiedArray = shallowCopy(grid);
    int temp = grid[0+x][0+y];
    copiedArray[0+x][0+y] = grid[1+x][0+y];
    copiedArray[1+x][0+y] = grid[1+x][1+y];
    copiedArray[1+x][1+y] = grid[0+x][1+y];
    copiedArray[0+x][1+y] = temp;
    return copiedArray;
}

void print_grid(int **grid)
{
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int check_grid(int **grid,int*locked_rows)
{
    //checks if pattern is sorted by line
    for(int i = 1; i < r;i++)
    {
        if(grid[i-1][0] > grid[i][0]) return 0;
    }
    // checks if all lines are full

    for(int i = 0; i < r;i++)
    {
        for(int j = 0; j < c;j++)
        {
            if(grid[i][0] != grid[i][j]) return 0;
        }
        if(locked_rows[i] == 0) locked_rows[i] = 1;
    }
    return 1;
}

//criar função para verificar se um dado padrão já se apresentou antes

int recursive_tries(int **grid,int*locked_moves,int moves)
{
    //number of handles for 2x2 grid = (columns-1) x (rows-1)
    //int x_handle = r-1;
    int **temp;
    //grid is already solved
    if(check_grid(grid,locked_moves))
    {
        clear_grid(grid);
        if(moves < best) best = moves;
        return 1;
    }
    if(moves >= m || moves >= best)
    {
        clear_grid(grid);
        return 0;
    }

    //r-1 = 1  c-1 = 2
    for(int i = 0; i < r-1; i++)
    {
        if(locked_moves[i] == 0 || locked_moves[i+1] == 0)
        {
            for(int j = 0; j < c-1; j++)
            {
                temp = rotate_left(grid,i,j);
                print_grid(temp);
                recursive_tries(temp,locked_moves,moves+1);
                clear_grid(temp);
                temp = rotate_right(grid,i,j);
                print_grid(temp);
                recursive_tries(temp,locked_moves,moves+1);
                clear_grid(temp);
            }
        }

    }
    return 0;
}


void aztec_vault(int*locked_rows)
{
    // ! verificar se os blocos são todos iguais
    // se os elementos na diagonal são iguais. só é necessário um movimento
    // a primeira linha só deve ter 1s, 2ºa linha só 2s...

    int count;


    int** grid = new int*[r];

    string input,dec;
    getline(cin,input);

    for(int i=0; i<r; i++)
    {
        grid[i] = new int[c];
        getline(cin,input);
        stringstream ss(input);
        count = 0;
        while (ss >> dec)
        {
            grid[i][count] = stoi(dec);
            count++;
        }
    }
    recursive_tries(grid,locked_rows,0);

    //adding initial pattern
    /*
    print_grid(grid);
    print_grid(rotate_right(grid,0,0));
    print_grid(rotate_right(grid,0,0));
    print_grid(rotate_left(grid,0,1));
    */

}



int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        cin >> r >> c >> m;
        int locked_rows[r+1];
        fill(locked_rows,locked_rows+r+1,0);
        aztec_vault(locked_rows);
        if(best > m) cout << "the treasure is lost!\n";
        else cout << best << "\n";
        best = 13;
        //cout << patterns.capacity() << "\n";
        //patterns.clear();
        //patterns.shrink_to_fit();
    }
    //cout << patterns.capacity() << "\n";
    return 0;
}