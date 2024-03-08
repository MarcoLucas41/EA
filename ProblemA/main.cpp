#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int rotations = 0;


// maximum number of rotations
int best = 13;
int locked_rows[7];

// number of rows, columns and total moves
int r,c,m;


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

void rotate_left(int **grid,int x,int y)
{
    //(0,1)
    int temp;
    temp = grid[0 + x][0 + y];
    grid[0 + x][0 + y] = grid[0 + x][1 + y];
    grid[0 + x][1 + y] = grid[1 + x][1 + y];
    grid[1 + x][1 + y] = grid[1 + x][0 + y];
    grid[1 + x][0 + y] = temp;

}

void rotate_right(int **grid,int x,int y)
{
    int temp;
    temp = grid[0+x][0+y];
    grid[0+x][0+y] = grid[1+x][0+y];
    grid[1+x][0+y] = grid[1+x][1+y];
    grid[1+x][1+y] = grid[0+x][1+y];
    grid[0+x][1+y] = temp;

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

int check_grid(int **grid)
{
    //checks if pattern is sorted by line
    for(int i = 1; i < r;i++)
    {
        if(grid[i-1][0] > grid[i][0]) return 0;
    }

    //checks if all lines are full
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




int recursive_tries(int **grid,int x, int y,int moves)
{
    //number of handles for 2x2 grid = (columns-1) x (rows-1)
    //int x_handle = r-1;
    int increment;
    int found;

    //grid is already solved
    if(check_grid(grid))
    {
        if(moves < best) best = moves;
        return 1;
    }
    if(moves >= m || moves >= best)
    {
        return 0;
    }

    //r-1 = 1  c-1 = 2
    for(int i = 0; i < r-1; i++)
    {
        for(int j = 0; j < c-1; j++)
        {
            if(i != x || j != y)
            {
                found = 0;
                increment = 1;
                while(increment <= 4)
                {
                    cout << "LEFT (" << i << "," << j << ") ROTATE " << increment <<" TOTAL MOVES " << moves <<"\n";
                    rotate_left(grid,i,j);
                    rotations++;
                    print_grid(grid);
                    if(recursive_tries(grid,i,j,moves+increment)) found = 1;
                    increment++;
                }
                if(found)
                {
                    increment = 1;
                    while(increment <= 4)
                    {
                        cout << "RIGHT (" << i << "," << j << ") ROTATE " << increment <<" TOTAL MOVES " << moves <<"\n";
                        rotate_right(grid,i,j);
                        rotations++;
                        print_grid(grid);
                        recursive_tries(grid,i,j,moves+increment);
                        increment++;
                    }
                }
            }
        }
    }
    return 0;
}


void aztec_vault()
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

    recursive_tries(grid,-1,-1,0);
    clear_grid(grid);


}



int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        cin >> r >> c >> m;
        aztec_vault();
        if(best > m) cout << "the treasure is lost!\n";
        else cout << best << "\n";
        best = 13;

        for(int & locked_row : locked_rows)
        {
            //cout << locked_row << " ";
            locked_row = 0;
        }
    }
    cout << "\n";
    cout << "Number of rotations: " << rotations << "\n";
    return 0;
}