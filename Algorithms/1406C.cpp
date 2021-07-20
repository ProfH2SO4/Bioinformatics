#include <bits/stdc++.h>

using namespace std;


/**
 * problem can be found at https://codeforces.com/problemset/problem/1406/C
 * useful links for explaining what centroid/centroid decomposition is
 * https://www.geeksforgeeks.org/centroid-decomposition-of-tree/
 * https://www.youtube.com/watch?v=-Lgda-6_AiY&t=861s
 *
 */
struct tree_info{
    vector<vector<int>> tree;
    vector<bool> visited;
    vector<int> values;
    int first_centroid;
    int second_centroid;


};

void solve(struct tree_info *struct_tree_info, int cur_node){

    struct_tree_info->visited[cur_node] = true;
    if(struct_tree_info->tree[cur_node].size() < 2 && cur_node != 1){ // leaf
        struct_tree_info->values[cur_node]++;
        return;
    }


    int level_sum_nodes = 0; // cur_node
    for(auto node: struct_tree_info->tree[cur_node]){
        if(!struct_tree_info->visited[node]){
            solve(struct_tree_info,node);
        }
        level_sum_nodes += struct_tree_info->values[node];

    }
    // all counted nodes under cur_node node + 1 cuz cur_node
    struct_tree_info->values[cur_node] = level_sum_nodes + 1 ;

}

void check(struct tree_info *struct_tree_info, int cur_node){
    bool can_be_centroid = true;
    int sum_childnodes = 0;
    int num_nodes = (struct_tree_info->tree.size()) - 1;

    struct_tree_info->visited[cur_node] = false;
    for(auto node: struct_tree_info->tree[cur_node]) {
        if (struct_tree_info->visited[node]) {
            if (struct_tree_info->values[node] > num_nodes / 2) {
                can_be_centroid = false;  // cur_node cant be centroid
            }
            sum_childnodes += struct_tree_info->values[node];
        }
    }

    if(can_be_centroid && num_nodes - (sum_childnodes +1) > num_nodes/2){
        can_be_centroid = false; // e.g leaf on other side of tree
        }

    if(can_be_centroid){
        if(struct_tree_info->first_centroid == -1) {
            struct_tree_info->first_centroid = cur_node;
        }
        else{
            struct_tree_info->second_centroid = cur_node;
        }
    }

    for(auto node: struct_tree_info->tree[cur_node]){
        if (struct_tree_info->visited[node]) {
            check(struct_tree_info, node);
        }
    }
}

int main(){
    int num_test;
    scanf("%d", &num_test);

    while(num_test--){
        int num_nodes;
        scanf("%d", &num_nodes);
        struct tree_info struct_tree_info;

        struct_tree_info.tree.resize(num_nodes+1);

        int x,y;
        for(auto i = 0; i < num_nodes-1; ++i){
            scanf("%d %d", &x, &y);
            struct_tree_info.tree[x].push_back(y);
            struct_tree_info.tree[y].push_back(x);
        }

        struct_tree_info.first_centroid = struct_tree_info.second_centroid = -1;
        struct_tree_info.visited.resize(num_nodes +1);
        struct_tree_info.values.resize(num_nodes +1);

        solve(&struct_tree_info,1);
        check(&struct_tree_info,1);

        if(struct_tree_info.second_centroid == -1){ // if is only one
            cout << 1 << " " << struct_tree_info.tree[1][0] << endl;
            cout << 1 << " " << struct_tree_info.tree[1][0] << endl;
        }
        else{
            int first_centroid= struct_tree_info.first_centroid;
            for(auto node : struct_tree_info.tree[first_centroid]){
                if(node == struct_tree_info.second_centroid) {continue;}
                cout <<first_centroid << " " << node << endl;
                cout <<struct_tree_info.second_centroid << " " << node << endl;
                break;
            }
        }


//        for(auto i= 1; i<= num_nodes; ++i){
//            cout << i << " " << struct_tree_info.values[i] << endl;
//        }
    }
    return 0;
}
