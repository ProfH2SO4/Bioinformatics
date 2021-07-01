#include <bits/stdc++.h>

/**
 * @ProfH2SO4
 * problem can be found at
 * https://codeforces.com/problemset/problem/1487/C
 */
using namespace std;


tuple<int, int> find_team(vector<deque<int>> &adj, int desired_team){
    for(vector<int>::size_type i = 1; i != adj.size(); ++i){
        if(adj[i][0] == 0){ // stop resizing
            adj[i].resize(0);
        }
        for(auto j =0; j< adj[i].size();++j){
            if(desired_team == adj[i][j]){
                adj[i].pop_back();
                return make_tuple(i, adj[i][j]);
            }
        }
    }
    return make_tuple(-1, -1);
}

tuple<int, int> draws(vector<deque<int>> &adj){

    for(vector<int>::size_type i = 1; i != adj.size(); i++){
        for(auto j =0; j < adj[i].size();++j) {
            adj[i].pop_back();
            return make_tuple(i, adj[i][j]);
            }
        }
    return make_tuple(-1, -1);
}

void solve(vector<deque<int>> adj, int num_teams){
    int num_iteration = (num_teams + 1) / 2;
    int scores[num_teams+1][num_teams+1];
    for(int j = 0; j < num_teams +1; ++j){
        for(int k = 0; k < num_teams + 1;++k){
            scores[j][k] = -5;
        }
    }

    for(auto i = 1; i <= num_iteration; ++i) {
        int first_team = 1;
        int second_team;
        int match_counter = 0;
        if(i == num_iteration && num_teams % 2 != 0){ // last round if odd
            break;
        }
        // i - 1 => last two pos in stop vector resizing, can be if[i][0] == 0, resize to 0
        while (match_counter < num_teams && first_team + i -1 < num_teams) {
            second_team = first_team + i;

            if (i == num_iteration && num_teams % 2 == 0) { // last round if even, must be n/2 draws
                for(auto k =0; k< num_teams /2;++k){
                tuple<int, int> draw_teams = draws(adj);
                if (get<0>(draw_teams) != -1) {
                    scores[get<0>(draw_teams)][get<1>(draw_teams)] = 0;
                    }
                }
                break;
            }
            scores[first_team][second_team] = 1; // win
            adj[first_team].pop_front();
            if(adj[second_team].empty() ){
                tuple<int, int> teams = find_team(adj, second_team);
                if (get<0>(teams) != -1) {
                    scores[get<0>(teams)][get<1>(teams)] = -1;
                }
            }
            first_team += 1;
            match_counter++;
        }

    }

    for(int j = 1; j < num_teams +1; ++j){
        for(int k = 0; k < num_teams + 1;++k){
            if(scores[j][k] != -5){
                cout << scores[j][k] << " ";
            }
        }
    }
}

void input(){
    int num_teams ;
    scanf("%d", &num_teams);
    vector<deque<int>> adj(num_teams+1);
    for(int i = 1; i <= num_teams; ++i){
        for(int j = i + 1; j <= num_teams;++j){
            adj[i].push_back(j);
        }
    }
    solve(adj, num_teams);
    cout << endl;
}


int main(){
    int num_test;
    scanf("%d", &num_test);
    for(int i =0; i < num_test;++i){
        input();
    }
}
