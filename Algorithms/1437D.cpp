#include <bits/stdc++.h>

/**
 * @ProfH2SO4
 * task can be found at
 * https://codeforces.com/problemset/problem/1437/D
 */
using namespace std;


void solve(vector<int> nodes){
    vector<deque<int>> tree; // not needed, used for better visualization
    int number_level = 0;
    tree.resize(number_level+1);
    deque<int> current_level;
    nodes.push_back(nodes.back());
    int stop = 1;
    for(unsigned int k = 0; k< nodes.size(); ++k) {
        int current_node = nodes[k];
        if(current_level.empty() || k < stop){
            current_level.push_back(current_node);
        }
        else{
            auto j = k;
            tree.resize(number_level+1);
            while(!current_level.empty()){ // until parents are not empty
                current_node = current_level.front();
                tree[number_level].push_back(current_node);
                current_level.pop_front();
                for(;j < nodes.size()-1;++j){ // loop via children
                    if(nodes[j] > nodes[j+1]){ // 4 3
                        ++j;
                        break;
                    }
                }
            }
            stop = j; // cuz first for loop must take as many as possible
            number_level++;
            --k;
        }
    }

    cout << number_level - 1<< endl; // cuz root doesnt count as level

    // Uncomment to see every level of tree

    //    for(auto k =0; k< tree.size();++k){
//        cout << k << ": ";
//        for(auto node: tree[k]){
//            cout << node << " ";
//        }
//        cout << endl;
//    }
}


void input(){
    int num_nodes;
    scanf("%d", &num_nodes);
    vector<int> nodes;
    for(auto k =0; k < num_nodes;++k){ // get all nodes
        int n;
        scanf("%d", &n);
        nodes.push_back(n);
    }

    solve(nodes);

}


int main(){
    int num_tests = 0;
    scanf("%d", &num_tests);
    while(num_tests > 0){
        input();
        num_tests--;
    }
    return 0;
}

