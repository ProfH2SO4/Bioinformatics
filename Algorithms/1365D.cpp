#include <bits/stdc++.h>

using namespace std;
#define N 51
int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void print_grid(vector<vector<char>> grid){

    for(auto i = 0; i< grid.size();++i){
        for(auto j = 0; j < grid[i].size();++j) {
            cout << grid[i][j] << " ";
        }

        cout <<endl;
    }


}

// check if position is in grid
bool is_valid(int sur_i, int sur_j, int n, int m){
    if(sur_i >= 0 && sur_i < n && sur_j >= 0 && sur_j < m){
        return true;
    }

    return false;
}


void find_escape(vector<vector<char>> &grid, int count_good, int n, int m){
    int good_able_end = 0;

    if(grid[n-1][m-1] != '.' && count_good != 0){
        cout << "No" << endl;
        return;
    }
    queue<tuple<int, int>> path;
    bool visited[N][N] = {false};
    path.push(make_tuple(n-1, m-1));
    while(!path.empty()){
        int i = get<0> (path.front());
        int j = get<1> (path.front());

        if(visited[i][j]) {
            path.pop();
            continue;
        }
        if(grid[i][j] == 'G'){
            good_able_end++;
        }
        visited[i][j] = true;
        path.pop();
        for(auto k = 0; k < 4;++k){
            int sur_i = i + direction[k][0];
            int sur_j = j + direction[k][1];
            if(is_valid(sur_i, sur_j, n, m) && (grid[sur_i][sur_j] == '.' || grid[sur_i][sur_j] == 'G')){
                if(!visited[sur_i][sur_j]) {
                    path.push(make_tuple(sur_i, sur_j));
                }

            }
        }

    }


    if(good_able_end == count_good){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
}

void solve(vector<vector<char>> grid){

    int n = grid.size();
    int m = grid[0].size();
    int count_good = 0;
   // queue<tuple<int, int>> q;
    // make walls around bad guys
    for(auto i = 0; i< n;++i){
        for(auto j = 0; j < m;++j){
            if(grid[i][j] == 'G'){
                //q.push(make_tuple(i,j));
                count_good++;
            }
            if(grid[i][j] == 'B'){ // bad guy found
                for(auto k = 0; k < 4;++k){ // loop one step around surrounding
                    int sur_i = i + direction[k][0];
                    int sur_j = j + direction[k][1];
                    if(is_valid(sur_i, sur_j, n, m) && grid[sur_i][sur_j] == '.'){
                        grid[sur_i][sur_j] = '#';
                    }
                    // B and next G impossible
                    if(is_valid(sur_i, sur_j, n, m) && grid[sur_i][sur_j] == 'G'){
                        cout << "No" << endl;
                        return;
                    }
                }
            }
        }
    }

    //print_grid(grid);

    find_escape(grid ,count_good, n, m);
}


int main(){
    int num_tests;
    scanf("%d", &num_tests);
    while (num_tests > 0){
        int n, m;
        scanf("%d %d", &n, &m);
        vector<vector<char>> grid;
        for(auto row = 0; row < n; ++row){
            vector<char> one_row;
            char pos;
            for(auto col = 0; col < m; ++col){
                scanf("%c", &pos);
                if(pos == '\n'){ // dont push NL
                    col--;
                    continue;
                }
                one_row.push_back(pos);
            }
            grid.push_back(one_row);
        }
        solve(grid);
        num_tests--;
    }
}
